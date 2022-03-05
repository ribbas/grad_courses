#ifndef SEM_PRED_HPP
#define SEM_PRED_HPP

#include "Symtab.hpp"
#include <iostream>

class SemanticPredicate {
private:
    bool mainDeclared = false;
    std::string curFuncType = "";
    SymbolTable symtab;

    bool declareFunc(std::string funcName, std::string retType) {
        if (!symtab.contains(funcName)) {
            symtab.define(funcName, retType);
            curFuncType = retType;
            return true;
        } else {
            return false;
        }
    }

    void declareMain(std::string funcName) {
        if (funcName == "main") {
            mainDeclared = true;
        }
    }

public:
    bool isValidVarType(std::string typeName) {
        return (typeName == "int");
    }

    bool checkSymbol(std::string stmt) {
        return symtab.contains(stmt);
    }

    bool checkReturnType() {
        return (curFuncType != "int");
    }

    bool checkReturnType(std::string stmt) {
        std::cout << stmt << '\n';
        if (((curFuncType == "void") && !stmt.empty()) ||
            ((curFuncType == "int") && stmt.empty())) {
            return false;
        } else {
            return true;
        }
    }

    void addSymbol(std::string symbolName) {
        symtab.define(symbolName);
    }

    void addSymbol(std::string symbolName, std::string symbolType) {
        symtab.define(symbolName, symbolType);
    }

    std::string dump() {
        return symtab.dump();
    }

    bool canDeclareFunc(std::string funcName, std::string retType) {
        declareMain(funcName);
        if (mainDeclared && !(funcName == "main")) {
            return false;
        } else {
            return declareFunc(funcName, retType);
        }
    }
};

#endif