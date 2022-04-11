
// Generated from
// /home/ribbas/grad_courses/615_compiler_design_with_llvm/assn/07_CPIRGenWhile/Cminus.g4
// by ANTLR 4.9

#include "CminusBaseVisitor.h"

CminusBaseVisitor::CminusBaseVisitor(std::string fileName)
    : assignmentVar(""), errorFound(false), condInst(false), condV(nullptr),
      iterInst(false), iterV(nullptr), iterPN(nullptr), PB(nullptr),
      module(std::make_unique<llvm::Module>(fileName, *irContext)) {

    llvm::FunctionType* inputFuncType =
        llvm::FunctionType::get(llvm::Type::getInt32Ty(*irContext), false);
    llvm::Function::Create(inputFuncType, llvm::Function::ExternalLinkage,
                           "input", module.get());

    std::vector<llvm::Type*> argList = {llvm::Type::getInt32Ty(*irContext)};
    llvm::FunctionType* outputFuncType = llvm::FunctionType::get(
        llvm::Type::getVoidTy(*irContext), argList, false);
    llvm::Function::Create(outputFuncType, llvm::Function::ExternalLinkage,
                           "output", module.get());
}

void CminusBaseVisitor::printModule(std::ofstream& fd) {

    std::string irCode;
    llvm::raw_string_ostream irStdout(irCode);

    if (!errorFound) {
        module->print(irStdout, nullptr);
        fd << irStdout.str();
        irStdout.flush();
    }
    expStack.clear();
    namedAllocas.clear();
}

antlrcpp::Any CminusBaseVisitor::visitVar_declaration(
    CminusParser::Var_declarationContext* ctx) {

    if (ctx->size) {

        semantics.addVarSymbol(ctx->ID()->getText(),
                               std::stoi(ctx->size->getText().c_str()));

        llvm::ArrayType* arrayType =
            llvm::ArrayType::get(llvm::Type::getInt32Ty(*irContext),
                                 std::stoi(ctx->size->getText().c_str()));

        if (semantics.getCurFuncName() == GLOBAL) {

            module->getOrInsertGlobal(ctx->ID()->getText(), arrayType);
            llvm::GlobalVariable* gVar =
                module->getNamedGlobal(ctx->ID()->getText());
            gVar->setDSOLocal(true);
            gVar->setAlignment(llvm::MaybeAlign(4));

        } else {

            namedAllocas[ctx->ID()->getText()] = irBuilder->CreateAlloca(
                arrayType, nullptr, "tmp_" + ctx->ID()->getText());
        }

    } else {

        semantics.addVarSymbol(ctx->ID()->getText());

        if (semantics.getCurFuncName() == GLOBAL) {

            module->getOrInsertGlobal(ctx->ID()->getText(),
                                      irBuilder->getInt32Ty());
            llvm::GlobalVariable* gVar =
                module->getNamedGlobal(ctx->ID()->getText());
            gVar->setDSOLocal(true);
            gVar->setAlignment(llvm::MaybeAlign(4));

        } else {

            namedAllocas[ctx->ID()->getText()] =
                irBuilder->CreateAlloca(llvm::Type::getInt32Ty(*irContext),
                                        nullptr, "tmp_" + ctx->ID()->getText());
        }
    }

    return visitChildren(ctx);
}

antlrcpp::Any CminusBaseVisitor::visitFun_declaration(
    CminusParser::Fun_declarationContext* ctx) {

    std::string funcIdStr = ctx->ID()->getText();
    std::string funcTypeStr = ctx->fun_type_specifier()->getText();

    int funcNumArgs = ctx->param().size();
    if (semantics.canDeclareFunc(funcIdStr, funcTypeStr)) {
        semantics.addFuncSymbol(funcIdStr, funcTypeStr, funcNumArgs);

        llvm::Type* retType = nullptr;
        // check function return type
        if (funcTypeStr == "void") {
            retType = llvm::Type::getVoidTy(*irContext);
        } else {
            retType = llvm::Type::getInt32Ty(*irContext);
        }

        llvm::FunctionType* funcType = nullptr;
        std::vector<std::string> argNames;
        // check if function has params
        if (!funcNumArgs) {
            funcType = llvm::FunctionType::get(retType, false);
        } else {
            std::vector<llvm::Type*> argList = std::vector<llvm::Type*>(
                funcNumArgs, llvm::Type::getInt32Ty(*irContext));
            funcType = llvm::FunctionType::get(retType, argList, false);

            for (auto& i : ctx->param()) {
                argNames.push_back(i->ID()->getText());
            }
        }

        llvm::Function* func = llvm::Function::Create(
            funcType, llvm::Function::ExternalLinkage, funcIdStr, module.get());
        llvm::BasicBlock* basicBlock =
            llvm::BasicBlock::Create(*irContext, "entry", func);
        irBuilder->SetInsertPoint(basicBlock);

        // set names for all arguments
        unsigned argIdx = 0;
        std::string namedArg = "";
        for (llvm::Argument& arg : func->args()) {

            namedArg = argNames[argIdx++];
            semantics.addVarSymbol(namedArg);
            arg.setName(namedArg);

            // create alloca for all parameter values
            namedAllocas[namedArg] = irBuilder->CreateAlloca(
                llvm::Type::getInt32Ty(*irContext), nullptr, "tmp_" + namedArg);
        }

        // create store for all parameter values
        for (llvm::Argument& arg : func->args()) {
            irBuilder->CreateStore(&arg, namedAllocas[arg.getName().str()],
                                   false);
        }
        argNames.clear();

    } else {

        fprintf(
            stderr, "Line %lu: Cannot declare function: \"%s %s(int * %lu)\"\n",
            ctx->start->getLine(), ctx->fun_type_specifier()->getText().c_str(),
            ctx->ID()->getText().c_str(), ctx->param().size());
    }

    return visitChildren(ctx);
}

antlrcpp::Any CminusBaseVisitor::visitIteration_stmt(
    CminusParser::Iteration_stmtContext* ctx) {

    llvm::Function* func = irBuilder->GetInsertBlock()->getParent();
    llvm::BasicBlock* loopBB =
        llvm::BasicBlock::Create(*irContext, "loop", func);
    llvm::BasicBlock* afterloopBB =
        llvm::BasicBlock::Create(*irContext, "afterloop");

    irBuilder->CreateBr(loopBB);

    // emit loop value
    irBuilder->SetInsertPoint(loopBB);
    iterPN =
        irBuilder->CreatePHI(llvm::Type::getInt32Ty(*irContext), 2, "looptmp");

    // relational expression
    iterInst = true;
    visit(ctx->relational_exp());
    iterInst = false;
    iterPN->addIncoming(iterV, loopBB);

    // if expression
    iterInst = true;
    visit(ctx->statement());
    llvm::Value* loopV = iterV;
    iterInst = false;

    iterPN->addIncoming(loopV, afterloopBB);

    irBuilder->CreateCondBr(expStack.back(), loopBB, afterloopBB);
    expStack.pop_back();

    loopBB = irBuilder->GetInsertBlock();

    // emit else block
    func->getBasicBlockList().push_back(afterloopBB);
    irBuilder->SetInsertPoint(afterloopBB);

    llvm::verifyFunction(*func);

    return visitChildren(ctx);
}

antlrcpp::Any CminusBaseVisitor::visitSelection_stmt(
    CminusParser::Selection_stmtContext* ctx) {

    // relational expression
    visit(ctx->relational_exp());

    llvm::Function* func = irBuilder->GetInsertBlock()->getParent();
    llvm::BasicBlock* thenBB =
        llvm::BasicBlock::Create(*irContext, "then", func);
    llvm::BasicBlock* elseBB = llvm::BasicBlock::Create(*irContext, "else");
    llvm::BasicBlock* contBB = llvm::BasicBlock::Create(*irContext, "ifcont");

    irBuilder->CreateCondBr(expStack.back(), thenBB, elseBB);
    expStack.pop_back();

    // emit then value
    irBuilder->SetInsertPoint(thenBB);

    // if expression
    condInst = true;
    visit(ctx->then_cond);
    llvm::Value* thenV = condV;
    condInst = false;

    irBuilder->CreateBr(contBB);
    thenBB = irBuilder->GetInsertBlock();

    // emit else block
    func->getBasicBlockList().push_back(elseBB);
    irBuilder->SetInsertPoint(elseBB);

    // else condition exists
    llvm::Value* elseV;
    if (ctx->else_cond) {
        condInst = true;
        visit(ctx->else_cond);
        elseV = condV;
        condInst = false;
    }

    irBuilder->CreateBr(contBB);

    // emit else block
    func->getBasicBlockList().push_back(contBB);
    irBuilder->SetInsertPoint(contBB);

    llvm::PHINode* phiNode = nullptr;
    // else condition exists
    if (ctx->else_cond) {

        // phi node resolving then and else registers
        phiNode = irBuilder->CreatePHI(llvm::Type::getInt32Ty(*irContext), 2,
                                       "iftmp");
        phiNode->addIncoming(thenV, thenBB);
        phiNode->addIncoming(elseV, elseBB);

    } else {

        // phi node resolving only then register
        phiNode = irBuilder->CreatePHI(llvm::Type::getInt32Ty(*irContext), 1,
                                       "iftmp");
        phiNode->addIncoming(thenV, thenBB);
    }

    irBuilder->CreateRet(phiNode);
    llvm::verifyFunction(*func);

    return nullptr;
}

antlrcpp::Any CminusBaseVisitor::visitRelational_exp(
    CminusParser::Relational_expContext* ctx) {

    antlrcpp::Any expression = visitChildren(ctx);
    llvm::Value* right = expStack.back();
    expStack.pop_back();
    llvm::Value* left = expStack.back();
    expStack.pop_back();
    llvm::Value* result = nullptr;

    if (ctx->relop()->EQ()) {
        result = irBuilder->CreateICmpEQ(left, right, "eq");
    } else if (ctx->relop()->NEQ()) {
        result = irBuilder->CreateICmpNE(left, right, "ne");
    } else if (ctx->relop()->LT()) {
        result = irBuilder->CreateICmpSLT(left, right, "lt");
    } else if (ctx->relop()->GT()) {
        result = irBuilder->CreateICmpSGT(left, right, "gt");
    } else if (ctx->relop()->LTE()) {
        result = irBuilder->CreateICmpSLE(left, right, "le");
    } else if (ctx->relop()->GTE()) {
        result = irBuilder->CreateICmpSGE(left, right, "ge");
    }
    expStack.push_back(result);

    if (iterInst) {
        iterV = left;
    }

    return expression;
}

bool isNumber(const std::string& str) {

    for (char const& c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }

    return true;
}

antlrcpp::Any CminusBaseVisitor::visitAssignment_stmt(
    CminusParser::Assignment_stmtContext* ctx) {

    assignmentVar = ctx->ID()->getText();

    if (!semantics.checkSymbol(assignmentVar)) {

        fprintf(stderr, "Line: %lu: Variable '%s' was not declared\n",
                ctx->start->getLine(), assignmentVar.c_str());
        errorFound = true;
        return nullptr;
    }

    if (ctx->ASN()) {

        // if expression
        for (CminusParser::ExpContext*& i : ctx->exp()) {
            if (isNumber(i->getText())) {
                semantics.setValue(assignmentVar, std::stoi(i->getText()));
            }
            visit(i);

            if (ctx->size) {

                // TODO:
                // replace array loads with getelementptr
            }

            irBuilder->CreateStore(expStack.back(), namedAllocas[assignmentVar],
                                   false);
            expStack.pop_back();
        }
    }

    return nullptr;
}

antlrcpp::Any
CminusBaseVisitor::visitReturn_stmt(CminusParser::Return_stmtContext* ctx) {

    // if return value exists
    if (ctx->exp()) {

        // if function is void
        if (!semantics.canReturn()) {

            fprintf(stderr,
                    "Line %lu: Function \"%s\" of type 'void' cannot "
                    "return \"%s\"\n",
                    ctx->start->getLine(), semantics.getCurFuncName().c_str(),
                    ctx->exp()->getText().c_str());
            errorFound = true;
            return nullptr;

        } else {

            antlrcpp::Any retVal = visitChildren(ctx);

            if (condInst) {

                condV = expStack.back();

            } else {

                irBuilder->CreateRet(expStack.back());
                expStack.pop_back();
            }

            return retVal;
        }

    } else if (!ctx->exp()) {

        if (semantics.canReturn()) {

            fprintf(stderr,
                    "Line %lu: Function \"%s\" of type 'int' must return a "
                    "value\n",
                    ctx->start->getLine(), semantics.getCurFuncName().c_str());
            errorFound = true;
            return nullptr;

        } else {

            irBuilder->CreateRetVoid();
        }
    }

    return visitChildren(ctx);
}

antlrcpp::Any
CminusBaseVisitor::visitAdd_exp(CminusParser::Add_expContext* ctx) {

    bool isAdd = ctx->addop()->ADD();
    antlrcpp::Any expression = visitChildren(ctx);

    llvm::Value* right = expStack.back();
    expStack.pop_back();
    llvm::Value* left = expStack.back();
    expStack.pop_back();
    llvm::Value* result = nullptr;

    if (iterInst) {
        left = iterPN;
    }

    if (isAdd) {
        result = irBuilder->CreateAdd(left, right, "atmp");
    } else {
        result = irBuilder->CreateSub(left, right, "stmp");
    }
    expStack.push_back(result);

    if (condInst) {
        condV = result;
    } else if (iterInst) {
        iterV = result;
    }

    return expression;
}

antlrcpp::Any
CminusBaseVisitor::visitMult_exp(CminusParser::Mult_expContext* ctx) {

    bool isMult = ctx->multop()->MULT();
    antlrcpp::Any expression = visitChildren(ctx);

    llvm::Value* right = expStack.back();
    expStack.pop_back();
    llvm::Value* left = expStack.back();
    expStack.pop_back();
    llvm::Value* result = nullptr;

    if (iterInst) {
        left = iterPN;
    }

    if (isMult) {
        result = irBuilder->CreateMul(left, right, "mtmp");
    } else {
        result = irBuilder->CreateSDiv(left, right, "dtmp");
    }
    expStack.push_back(result);

    if (condInst) {
        condV = result;
    } else if (iterInst) {
        iterV = result;
    }

    return expression;
}

antlrcpp::Any
CminusBaseVisitor::visitVal_exp(CminusParser::Val_expContext* ctx) {

    if (!semantics.checkSymbol(ctx->ID()->getText())) {

        fprintf(stderr, "Line %lu: Variable '%s' was not declared\n",
                ctx->start->getLine(), ctx->ID()->getText().c_str());
        errorFound = true;
        return nullptr;

    } else {

        llvm::Value* value = irBuilder->CreateLoad(
            llvm::Type::getInt32Ty(*irContext),
            namedAllocas[ctx->ID()->getText()], "ltmp_" + ctx->ID()->getText());
        expStack.push_back(value);
        if (condInst) {
            condV = expStack.back();
        }
        return visitChildren(ctx);
    }
}

antlrcpp::Any
CminusBaseVisitor::visitNum_exp(CminusParser::Num_expContext* ctx) {

    llvm::Value* value = llvm::ConstantInt::get(
        llvm::Type::getInt32Ty(*irContext), std::stoi(ctx->getText()));

    if (condInst) {
        condV = value;
    }

    expStack.push_back(value);

    return visitChildren(ctx);
}

antlrcpp::Any
CminusBaseVisitor::visitCall_exp(CminusParser::Call_expContext* ctx) {

    llvm::Function* calleeFunc = module->getFunction(ctx->ID()->getText());
    std::vector<llvm::Value*> argsVector;

    if (!semantics.isValidNumArgs(ctx->ID()->getText(), ctx->exp().size())) {
        fprintf(stderr,
                "Line %lu: Call to '%s' has invalid number of arguments\n",
                ctx->start->getLine(), ctx->ID()->getText().c_str());
        errorFound = true;
        return nullptr;
    }

    // if call has params
    for (CminusParser::ExpContext*& i : ctx->exp()) {
        visit(i);
        argsVector.push_back(expStack.back());
        expStack.pop_back();
    }

    // if function is of type void and cannot return
    if (calleeFunc->getReturnType()->isVoidTy()) {

        irBuilder->CreateCall(calleeFunc, argsVector);

    } else {

        std::string callTmp = (assignmentVar.length() ? assignmentVar : "ctmp");
        expStack.push_back(
            irBuilder->CreateCall(calleeFunc, argsVector, callTmp));
    }

    return nullptr;
}