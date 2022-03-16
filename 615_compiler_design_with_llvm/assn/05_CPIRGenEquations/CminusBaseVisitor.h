
// Generated from
// /home/ribbas/grad_courses/615_compiler_design_with_llvm/assn/05_CPIRGenEquations/Cminus.g4
// by ANTLR 4.9

#pragma once

#include "CminusVisitor.h"
#include "antlr4-runtime.h"
#include <map>
#include <vector>

/**
 * This class provides an empty implementation of CminusVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the
 * available methods.
 */
class CminusBaseVisitor : public CminusVisitor {

private:
    std::string currentFuncName = "";

    // open a new context and module
    std::unique_ptr<llvm::LLVMContext> irContext =
        std::make_unique<llvm::LLVMContext>();

    // create a new builder for the module
    std::unique_ptr<llvm::IRBuilder<>> irBuilder =
        std::make_unique<llvm::IRBuilder<>>(*irContext);

    std::unique_ptr<llvm::Module> module =
        std::make_unique<llvm::Module>("moduleName", *irContext);
    std::map<std::string, llvm::Value*> namedValues;
    std::vector<CminusParser::Additive_expressionContext*> factors;

public:
    CminusBaseVisitor() {
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
    visitDeclaration_list(CminusParser::Declaration_listContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitDeclaration(CminusParser::DeclarationContext* ctx) override {

        if (ctx->fun_declaration()) {

            currentFuncName = ctx->fun_declaration()->ID()->getText();
            std::string paramList = ctx->fun_declaration()->params()->getText();
            int count = 1;
            for (int i = 0; i < paramList.size(); i++) {
                if (paramList[i] == ',') {
                    count++;
                }
            }

            llvm::Type* retType = nullptr;
            if (ctx->fun_declaration()->type_specifier()->getText() == "void") {
                retType = llvm::Type::getVoidTy(*irContext);
            } else {
                retType = llvm::Type::getInt32Ty(*irContext);
            }

            llvm::FunctionType* funcType = nullptr;
            std::vector<std::string> argNames;
            if (count == 1 && paramList == "void") {
                funcType = llvm::FunctionType::get(retType, false);
            } else {
                std::vector<llvm::Type*> argList = std::vector<llvm::Type*>(
                    count, llvm::Type::getInt32Ty(*irContext));
                funcType = llvm::FunctionType::get(retType, argList, false);

                for (auto& i :
                     ctx->fun_declaration()->params()->param_list()->children) {
                    if (i->getText() != ",") {
                        argNames.push_back(i->getText().substr(3));
                    }
                }
            }

            llvm::Function* func = llvm::Function::Create(
                funcType, llvm::Function::ExternalLinkage, currentFuncName,
                module.get());
            llvm::BasicBlock* BB =
                llvm::BasicBlock::Create(*irContext, "Entry", func);
            irBuilder->SetInsertPoint(BB);

            // Set names for all arguments.
            unsigned Idx = 0;
            std::string namedArg = "";
            for (llvm::Argument& Arg : func->args()) {
                namedArg = argNames[Idx++];
                Arg.setName(namedArg);
                namedValues[namedArg] = &Arg;
            }
        }

        auto lol = visitChildren(ctx);
        std::cout << "DONOENODNSNDSND\n";

        for (auto& i : factors) {
            std::cout << "ayo " << i->getText() << "\n";
        }
        factors.clear();

        return lol;
    }

    virtual antlrcpp::Any
    visitVar_declaration(CminusParser::Var_declarationContext* ctx) override {

        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitType_specifier(CminusParser::Type_specifierContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitFun_declaration(CminusParser::Fun_declarationContext* ctx) override {

        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitParams(CminusParser::ParamsContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitParam_list(CminusParser::Param_listContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitParam(CminusParser::ParamContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitCompound_statement(
        CminusParser::Compound_statementContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitLocal_declarations(
        CminusParser::Local_declarationsContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitStatement_list(CminusParser::Statement_listContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitStatement(CminusParser::StatementContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitExpression_statement(
        CminusParser::Expression_statementContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitSelection_statement(
        CminusParser::Selection_statementContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitIteration_statement(
        CminusParser::Iteration_statementContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitReturn_statement(CminusParser::Return_statementContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitExpression(CminusParser::ExpressionContext* ctx) override {
        std::cout << currentFuncName << "|" << ctx->getText() << "\n";
        if (ctx->simple_expression()) {

            for (CminusParser::Additive_expressionContext* addExprCtx :
                 ctx->simple_expression()->additive_expression()) {

                if (CminusParser::CallContext* callCtx =
                        addExprCtx->term()->factor()->call()) {

                    if (callCtx->args()->arg_list()) {
                        std::cout << "args|" << callCtx->args()->getText()
                                  << "\n";
                    }

                    llvm::Function* calleeFunc =
                        module->getFunction(callCtx->ID()->getText());
                    if (!calleeFunc) {

                        std::cout << "failed call|" << callCtx->ID()->getText()
                                  << "\n";

                    } else {

                        if (calleeFunc->getReturnType()->isVoidTy()) {

                            irBuilder->CreateCall(calleeFunc);

                        } else {

                            if (ctx->var()) {
                                // std::cout << "var|"
                                //           << ctx->var()->ID()->getText()
                                //           << "\n";

                                std::vector<llvm::Value*> ArgsV;
                                irBuilder->CreateCall(
                                    calleeFunc, ArgsV,
                                    ctx->var()->ID()->getText());
                            }
                        }
                    }

                } else {

                    // for (auto& i : addExprCtx->children) {
                    //     std::cout << "ayo "
                    //               <<
                    //               dynamic_cast<antlr4::tree::ParseTree*>(i)
                    //               << "\n";
                    // }

                    factors.push_back(addExprCtx);

                    std::cout << "what am I doing "
                              << addExprCtx->term()->getText() << '\n';

                    // if (addExprCtx->additive_expression() &&
                    //     addExprCtx->term()) {
                    //     std::cout << "maybe this one\n";
                    // }

                    // if (addExprCtx->term()) {
                    //     std::cout << "term|" << addExprCtx->term()->getText()
                    //               << "\n";
                    // }
                    // CminusParser::TermContext* termCur = addExprCtx->term();
                    // while (termCur) {
                    //     std::cout << "term|" << termCur->getText() << "\n";
                    //     termCur = termCur->term();
                    // }

                    // CminusParser::Additive_expressionContext* addExprCur =
                    //     addExprCtx->additive_expression();
                    // while (addExprCur) {
                    //     std::cout << "additive_expression|"
                    //               << addExprCur->getText() << "\n";
                    //     addExprCur = addExprCur->additive_expression();
                    // }

                    // std::cout << "exp|" << addExprCtx->getText() << "\n";
                }
                std::cout << "\n";
                return visitAdditive_expression(addExprCtx);
            }
        }
        std::cout << "didn't escape\n";
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitVar(CminusParser::VarContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitSimple_expression(
        CminusParser::Simple_expressionContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitRelop(CminusParser::RelopContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitAdditive_expression(
        CminusParser::Additive_expressionContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitAddop(CminusParser::AddopContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitTerm(CminusParser::TermContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitMulop(CminusParser::MulopContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitFactor(CminusParser::FactorContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitCall(CminusParser::CallContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitArgs(CminusParser::ArgsContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitArg_list(CminusParser::Arg_listContext* ctx) override {
        return visitChildren(ctx);
    }
};
