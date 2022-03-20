
// Generated from
// /home/ribbas/grad_courses/615_compiler_design_with_llvm/assn/05_CPIRGenEquations/Cminus.g4
// by ANTLR 4.9

#pragma once

#include "CminusVisitor.h"
#include "IR_Gen.h"
#include "antlr4-runtime.h"
#include <stack>

/**
 * This class provides an empty implementation of CminusVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the
 * available methods.
 */
class CminusBaseVisitor : public CminusVisitor {

private:
    std::string assignmentVar = "";
    std::vector<llvm::Value*> opands;
    bool valIsOpand = false;
    std::map<std::string, llvm::Value*> namedAllocas;
    std::map<std::string, llvm::Value*> namedStores;
    std::map<std::string, llvm::Value*> namedLoads;

    std::unique_ptr<llvm::Module> module = nullptr;

public:
    CminusBaseVisitor(std::string fileName) {

        module = std::make_unique<llvm::Module>(fileName, *irContext);

        llvm::FunctionType* inputFuncType =
            llvm::FunctionType::get(llvm::Type::getInt32Ty(*irContext), false);
        llvm::Function* inputFunc = llvm::Function::Create(
            inputFuncType, llvm::Function::ExternalLinkage, "input",
            module.get());
        llvm::BasicBlock* inputBB =
            llvm::BasicBlock::Create(*irContext, "Entry", inputFunc);
        irBuilder->SetInsertPoint(inputBB);

        std::vector<llvm::Type*> argList =
            std::vector<llvm::Type*>(1, llvm::Type::getInt32Ty(*irContext));
        llvm::FunctionType* outputFuncType = llvm::FunctionType::get(
            llvm::Type::getVoidTy(*irContext), argList, false);
        llvm::Function* outputFunc = llvm::Function::Create(
            outputFuncType, llvm::Function::ExternalLinkage, "output",
            module.get());
        llvm::BasicBlock* outputBB =
            llvm::BasicBlock::Create(*irContext, "Entry", outputFunc);
        irBuilder->SetInsertPoint(outputBB);
    }

    void printModule() {
        module->print(llvm::errs(), nullptr);
    }

    virtual antlrcpp::Any
    visitProgram(CminusParser::ProgramContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitVar_declaration(CminusParser::Var_declarationContext* ctx) override {
        semantics.addSymbol(ctx->ID()->getText(), "int");
        namedAllocas[ctx->ID()->getText()] =
            irBuilder->CreateAlloca(llvm::Type::getInt32Ty(*irContext), nullptr,
                                    "atmp_" + ctx->ID()->getText());
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitFun_declaration(CminusParser::Fun_declarationContext* ctx) override {

        std::string funcIdStr = ctx->ID()->getText();
        std::string funcTypeStr = ctx->fun_type_specifier()->getText();

        int funcNumArgs = ctx->param().size();
        if (semantics.canDeclareFunc(funcIdStr, funcTypeStr)) {
            semantics.addSymbol(funcIdStr, funcTypeStr, funcNumArgs);

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
                funcType, llvm::Function::ExternalLinkage, funcIdStr,
                module.get());
            llvm::BasicBlock* basicBlock =
                llvm::BasicBlock::Create(*irContext, "Entry", func);
            irBuilder->SetInsertPoint(basicBlock);

            // set names for all arguments
            unsigned argIdx = 0;
            std::string namedArg = "";
            for (llvm::Argument& arg : func->args()) {

                namedArg = argNames[argIdx++];
                semantics.addSymbol(namedArg, "int");
                arg.setName(namedArg);

                // create alloca for all parameter values
                namedAllocas[namedArg] =
                    irBuilder->CreateAlloca(llvm::Type::getInt32Ty(*irContext),
                                            nullptr, "atmp_" + namedArg);
            }

            // create store for all parameter values
            for (llvm::Argument& arg : func->args()) {
                namedStores[arg.getName().str()] = irBuilder->CreateStore(
                    &arg, namedAllocas[arg.getName().str()], false);
            }
            argNames.clear();

        } else {

            fprintf(stderr, "Cannot declare function: \"%s %s(int * %lu)\"\n",
                    ctx->fun_type_specifier()->getText().c_str(),
                    ctx->ID()->getText().c_str(), ctx->param().size());
        }

        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitFun_type_specifier(
        CminusParser::Fun_type_specifierContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitParam(CminusParser::ParamContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitCompound_stmt(CminusParser::Compound_stmtContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitStatement(CminusParser::StatementContext* ctx) override {

        if (ctx->assignment_stmt()) {

            assignmentVar = ctx->assignment_stmt()->ID()->getText();

        } else if (ctx->exp()) {

            std::cout << "expsdsd " << ctx->exp()->getText() << "\n";
        }

        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitSelection_stmt(CminusParser::Selection_stmtContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitIteration_stmt(CminusParser::Iteration_stmtContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitAssignment_stmt(CminusParser::Assignment_stmtContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitReturn_stmt(CminusParser::Return_stmtContext* ctx) override {

        valIsOpand = false;

        // if return value exists
        if (ctx->exp()) {

            std::string retValueStr = ctx->exp()->getText();

            // if function is void
            if (!semantics.canReturn()) {

                fprintf(stderr,
                        "Function \"%s\" of type 'void' cannot return \"%s\"\n",
                        semantics.getCurFuncName().c_str(),
                        retValueStr.c_str());
                return nullptr;

            } else {

                antlrcpp::Any retVal = visitChildren(ctx);
                llvm::Value* retAlloca = namedAllocas[retValueStr];

                if (retAlloca) {

                    irBuilder->CreateRet(irBuilder->CreateLoad(
                        llvm::Type::getInt32Ty(*irContext), retAlloca,
                        "ltmp_" + retValueStr));

                } else {

                    irBuilder->CreateRet(llvm::ConstantInt::get(
                        llvm::Type::getInt32Ty(*irContext),
                        std::stoi(retValueStr)));
                }

                return retVal;
            }

        } else if (!ctx->exp()) {

            if (semantics.canReturn()) {

                fprintf(stderr,
                        "Function \"%s\" of type 'int' must return a value\n",
                        semantics.getCurFuncName().c_str());
                return nullptr;

            } else {

                irBuilder->CreateRetVoid();
            }
        }

        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitAdd_exp(CminusParser::Add_expContext* ctx) override {

        std::cout << "adding <" << ctx->exp().front()->getText() << "><"
                  << ctx->addop()->getText() << "><"
                  << ctx->exp().back()->getText() << ">\n";
        valIsOpand = true;
        auto expl = visitChildren(ctx);

        llvm::Value* right = opands.back();
        opands.pop_back();
        llvm::Value* left = opands.back();
        opands.pop_back();
        llvm::Value* result = irBuilder->CreateAdd(left, right, "atmp");
        opands.push_back(result);

        return expl;
    }

    virtual antlrcpp::Any
    visitMult_exp(CminusParser::Mult_expContext* ctx) override {

        std::cout << "multing <" << ctx->exp().front()->getText() << "><"
                  << ctx->multop()->getText() << "><"
                  << ctx->exp().back()->getText() << ">\n";
        valIsOpand = true;
        auto expl = visitChildren(ctx);

        llvm::Value* right = opands.back();
        opands.pop_back();
        llvm::Value* left = opands.back();
        opands.pop_back();
        llvm::Value* result = irBuilder->CreateMul(left, right, "mtmp");
        opands.push_back(result);

        return expl;
    }

    virtual antlrcpp::Any
    visitParen_exp(CminusParser::Paren_expContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitVal_exp(CminusParser::Val_expContext* ctx) override {

        std::cout << "value " << ctx->getText();
        if (valIsOpand) {
            namedLoads[ctx->getText()] = irBuilder->CreateLoad(
                llvm::Type::getInt32Ty(*irContext),
                namedAllocas[ctx->getText()], "ltmp_" + ctx->getText());
            opands.push_back(namedLoads[ctx->getText()]);
            std::cout << " loaded\n";
        }
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitNum_exp(CminusParser::Num_expContext* ctx) override {

        std::cout << "num " << ctx->getText();
        if (valIsOpand) {
            namedLoads[ctx->getText()] = llvm::ConstantInt::get(
                llvm::Type::getInt32Ty(*irContext), std::stoi(ctx->getText()));
            opands.push_back(namedLoads[ctx->getText()]);
            std::cout << " loaded\n";
        }

        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitCall_exp(CminusParser::Call_expContext* ctx) override {

        std::cout << "call " << ctx->getText() << '\n';
        llvm::Function* calleeFunc = module->getFunction(ctx->ID()->getText());
        if (calleeFunc->getReturnType()->isVoidTy()) {

            irBuilder->CreateCall(calleeFunc);

        } else {
            std::vector<llvm::Value*> ArgsV;
            llvm::Value* callValue =
                irBuilder->CreateCall(calleeFunc, ArgsV, assignmentVar);
            namedStores[assignmentVar] = irBuilder->CreateStore(
                callValue, namedAllocas[assignmentVar], false);
        }
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitRelational_exp(CminusParser::Relational_expContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitAddop(CminusParser::AddopContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitMultop(CminusParser::MultopContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitRelop(CminusParser::RelopContext* ctx) override {
        return visitChildren(ctx);
    }
};
