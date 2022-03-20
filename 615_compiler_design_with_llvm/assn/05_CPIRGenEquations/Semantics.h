#ifndef SEM_PRED_H
#define SEM_PRED_H

#include "Symtab.h"
#include <iostream>

class Semantics {
private:
    bool mainDeclared = false;
    std::string curFuncName = "";
    std::string curFuncType = "";
    SymbolTable symtab;

    bool declareFunc(std::string funcName, std::string retType) {
        if (!symtab.contains(funcName)) {
            symtab.define(funcName, retType, 0);
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
    void addSymbol(std::string symbolName, std::string symbolType) {
        symtab.define(symbolName, symbolType);
    }

    void addSymbol(std::string symbolName, std::string symbolType,
                   int numArgs) {
        symtab.define(symbolName, symbolType, numArgs);
    }

    bool checkSymbol(std::string stmt) {
        return symtab.contains(stmt);
    }

    bool canReturn() {
        return (curFuncType == "int");
    }

    void setCurFuncName(std::string funcName) {
        curFuncName = funcName;
    }

    std::string getCurFuncName() {
        return curFuncName;
    }

    bool isValidNumArgs(std::string funcName, int numParams) {

        return (symtab.getNumArgs(funcName) == numParams);
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