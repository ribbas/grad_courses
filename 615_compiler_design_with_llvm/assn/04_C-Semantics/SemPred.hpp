#ifndef SEM_PRED_HPP
#define SEM_PRED_HPP

#include "Symtab.hpp"
#include <iostream>

class SemanticPredicate {
private:
    bool mainDeclared = false;
    std::string curFuncName = "";
    std::string curFuncType = "";
    SymbolTable symtab;

    bool declareFunc(std::string funcName, std::string retType) {
        if (!symtab.contains(funcName)) {
            symtab.define(funcName, retType);
            curFuncName = funcName;
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
    bool canReturn(std::string symbolName) {
        symbolName = symbolName.substr(0, symbolName.length() - 2);
        return (symtab.getType(symbolName) == "int");
    }

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
        if (((curFuncType == "void") && !stmt.empty()) ||
            ((curFuncType == "int") && stmt.empty())) {
            return false;
        } else {
            return true;
        }
    }

    void setNumArgs(std::string paramList) {

        int count = 1;
        for (int i = 0; i < paramList.size(); i++) {
            if (paramList[i] == ',') {
                count++;
            }
        }
        symtab.setNumArgs(curFuncName, count);
    }

    void addSymbol(std::string symbolName) {
        symtab.define(symbolName);
    }

    void addSymbol(std::string symbolName, std::string symbolType) {
        symtab.define(symbolName, symbolType);
    }

    bool canDeclareFunc(std::string funcName, std::string retType) {
        declareMain(funcName);
        if (mainDeclared && !(funcName == "main")) {
            return false;
        } else {
            return declareFunc(funcName, retType);
        }
    }

    std::string dump() {
        return symtab.dump();
    }
};

#endif