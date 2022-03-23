#ifndef SEM_PRED_H
#define SEM_PRED_H

#include "Symtab.h"
#include <iostream>

class Semantics {
private:
    bool mainDeclared = false;
    std::string curFuncName = "global";
    std::string curFuncType = "";
    SymbolTable symtab;

    bool declareFunc(std::string funcName, std::string retType) {
        if (!symtab.contains(funcName, "global")) {
            symtab.defineFunc(funcName, retType, 0);
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
    void addVarSymbol(std::string symbolName, int size = 0) {
        symtab.defineVar(symbolName, "int", curFuncName, size);
    }

    void addFuncSymbol(std::string symbolName, std::string symbolType,
                       int numArgs) {
        symtab.defineFunc(symbolName, symbolType, numArgs);
    }

    bool checkSymbol(std::string symbolName) {
        return symtab.contains(symbolName, curFuncName);
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

        return (symtab.getNumArgs(funcName, "global") == numParams);
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