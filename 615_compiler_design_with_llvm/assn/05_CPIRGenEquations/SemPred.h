#ifndef SEM_PRED_H
#define SEM_PRED_H

#include "Symtab.h"
#include <iostream>

class SemanticPredicate {
private:
  bool mainDeclared = false;
  std::string curFuncName = "";
  std::string curFuncType = "";
  SymbolTable symtab;

  bool declareFunc(std::string funcName, std::string retType) {
    if (!symtab.contains(funcName)) {
      symtab.define(funcName, retType, 0, true);
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

  int countParams(std::string paramList) {

    int count = 1;
    for (int i = 0; i < paramList.size(); i++) {
      if (paramList[i] == ',') {
        count++;
      }
    }

    return count;
  }

public:
  bool canReturn(std::string symbolName) {
    std::string substr = symbolName.substr(0, symbolName.length() - 2);
    if (symtab.isFunc(substr)) {
      return (symtab.getType(substr) == "int");
    } else {
      return true;
    }
  }

  bool isValidVarType(std::string typeName) { return (typeName == "int"); }

  bool checkSymbol(std::string stmt) { return symtab.contains(stmt); }

  bool checkReturnType() { return (curFuncType != "int"); }

  bool checkReturnType(std::string stmt) {
    if (((curFuncType == "void") && !stmt.empty()) ||
        ((curFuncType == "int") && stmt.empty())) {
      return false;
    } else {
      return true;
    }
  }

  void setCurFuncName(std::string funcName) { curFuncName = funcName; }

  void setNumArgs(std::string paramList) {

    symtab.setNumArgs(curFuncName, countParams(paramList));
  }

  bool isValidNumArgs(std::string paramList) {

    return (symtab.getNumArgs(curFuncName) == countParams(paramList));
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

  std::string dump() { return symtab.dump(); }
};

#endif