#ifndef SEM_PRED_HPP
#define SEM_PRED_HPP

#include "Symtab.hpp"
#include <iostream>

class SemanticPredicate {
    bool mainDeclared = false;

public:
    SymbolTable symtab;

    std::string dump() {
        return symtab.dump();
    }

    bool declareFun(std::string funcName, std::string retType) {
        if (!symtab.contains(funcName)) {
            symtab.define(funcName, retType);
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

    bool canDeclareFun(std::string funcName, std::string retType) {
        declareMain(funcName);
        if (mainDeclared && !(funcName == "main")) {
            return false;
        } else {
            return declareFun(funcName, retType);
        }
    }
};

#endif