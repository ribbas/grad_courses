
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
                funcType, llvm::Function::ExternalLinkage,
                ctx->fun_declaration()->ID()->getText(), module.get());
            llvm::BasicBlock* BB =
                llvm::BasicBlock::Create(*irContext, "Entry", func);
            irBuilder->SetInsertPoint(BB);

            // Set names for all arguments.
            unsigned Idx = 0;
            std::string namedArg = "";
            for (auto& Arg : func->args()) {
                namedArg = argNames[Idx++];
                Arg.setName(namedArg);
                namedValues[namedArg] = &Arg;
            }
        }
        module->print(llvm::errs(), nullptr);
        return visitChildren(ctx);
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
