
// Generated from
// /home/ribbas/grad_courses/615_compiler_design_with_llvm/assn/05_CPIRGenEquations/Cminus.g4
// by ANTLR 4.9

#pragma once

#include "CminusVisitor.h"
#include "antlr4-runtime.h"

/**
 * This class provides an empty implementation of CminusVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the
 * available methods.
 */
class CminusBaseVisitor : public CminusVisitor {
private:
    std::string assignmentVar = "";
    llvm::Value* assignmentAlloca = nullptr;
    std::map<std::string, llvm::Value*> namedAllocas;

    // open a new context and module
    std::unique_ptr<llvm::LLVMContext> irContext =
        std::make_unique<llvm::LLVMContext>();

    // create a new builder for the module
    std::unique_ptr<llvm::IRBuilder<>> irBuilder =
        std::make_unique<llvm::IRBuilder<>>(*irContext);

    std::unique_ptr<llvm::Module> module =
        std::make_unique<llvm::Module>("moduleName", *irContext);
    std::map<std::string, llvm::Value*> namedValues;

public:
    CminusBaseVisitor() {
        llvm::FunctionType* inputFuncType =
            llvm::FunctionType::get(llvm::Type::getInt32Ty(*irContext), false);
        llvm::Function* inputFunc = llvm::Function::Create(
            inputFuncType, llvm::Function::ExternalLinkage, "input",
            module.get());
        llvm::BasicBlock* inputBB = llvm::BasicBlock::Create(
            *irContext, "<builtin IO functionality>", inputFunc);
        irBuilder->SetInsertPoint(inputBB);

        std::vector<llvm::Type*> argList =
            std::vector<llvm::Type*>(1, llvm::Type::getInt32Ty(*irContext));
        llvm::FunctionType* outputFuncType = llvm::FunctionType::get(
            llvm::Type::getVoidTy(*irContext), argList, false);
        llvm::Function* outputFunc = llvm::Function::Create(
            outputFuncType, llvm::Function::ExternalLinkage, "output",
            module.get());
        llvm::BasicBlock* outputBB = llvm::BasicBlock::Create(
            *irContext, "<builtin IO functionality>", outputFunc);
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
        namedAllocas[ctx->ID()->getText()] = irBuilder->CreateAlloca(
            llvm::Type::getInt32Ty(*irContext), nullptr, ctx->ID()->getText());
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
                // if function returns int
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

            // Set names for all arguments.
            unsigned argIdx = 0;
            std::string namedArg = "";
            for (llvm::Argument& arg : func->args()) {
                namedArg = argNames[argIdx++];
                arg.setName(namedArg);
                namedValues[namedArg] = &arg;
            }

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

            std::cout << "exp " << ctx->assignment_stmt()->ID()->getText();
            assignmentVar = ctx->assignment_stmt()->ID()->getText();
            std::cout << "=" << ctx->assignment_stmt()->exp().front()->getText()
                      << "\n";
        }
        // for (auto& i : ctx->exp()) {
        //     std::cout << "exp " << i->getText() << "\n";
        // }

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
        if (ctx->return_value() && !semantics.canReturn()) {
            fprintf(stderr,
                    "Function \"%s\" of void type cannot return \"%s\"\n",
                    semantics.getCurFuncName().c_str(),
                    ctx->return_value()->getText().c_str());
        } else if (!ctx->return_value() && semantics.canReturn()) {
            fprintf(stderr, "Function \"%s\" of int type must return a value\n",
                    semantics.getCurFuncName().c_str());
        }
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitReturn_value(CminusParser::Return_valueContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitAdd_exp(CminusParser::Add_expContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitParen_exp(CminusParser::Paren_expContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitNum_exp(CminusParser::Num_expContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitCall_exp(CminusParser::Call_expContext* ctx) override {

        std::cout << "call " << ctx->getText() << '\n';
        llvm::Function* calleeFunc = module->getFunction(ctx->ID()->getText());
        if (calleeFunc->getReturnType()->isVoidTy()) {

            irBuilder->CreateCall(calleeFunc);
            std::cout << "created call\n";

        } else {
            std::vector<llvm::Value*> ArgsV;
            llvm::Value* callValue = irBuilder->CreateCall(calleeFunc, ArgsV);
            irBuilder->CreateStore(callValue, namedAllocas[assignmentVar],
                                   false);
        }
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitVal_exp(CminusParser::Val_expContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitMult_exp(CminusParser::Mult_expContext* ctx) override {
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
