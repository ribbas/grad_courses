#ifndef SYMTAB_H
#define SYMTAB_H

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

class Symbol {
private:
    int numArgs = 0;
    std::string name;
    std::string type = "builtin";
    bool isFunc = false;
    std::string scope = "global";

public:
    Symbol(std::string _name, std::string _type, bool _isFunc)
        : name(_name), type(_type), isFunc(_isFunc) {}

    Symbol(std::string _name, std::string _type, std::string scope,
           bool _isFunc)
        : name(_name), type(_type), scope(scope), isFunc(_isFunc) {}

    Symbol(std::string _name, std::string _type, int _numArgs, bool _isFunc)
        : name(_name), type(_type), numArgs(_numArgs), isFunc(_isFunc) {}

    void setIsFunc(bool _isFunc) {
        isFunc = _isFunc;
    }

    bool getIsFunc() {
        return isFunc;
    }

    void setNumArgs(int _numArgs) {
        numArgs = _numArgs;
    }

    std::string getType() {
        return type;
    }

    int getNumArgs() {
        return numArgs;
    }

    void setScopeName(std::string scopeName) {
        scope = scopeName;
    }

    std::string getScopeName() {
        return scope;
    }

    std::string toString() {
        if (type.length()) {
            return "<scope:" + scope + "><name:" + name + "><type:" + type +
                   "><" + (isFunc ? "func" : "var") +
                   "><narg:" + std::to_string(numArgs) + '>';
        }
        return name;
    }
};

class SymbolTable {
private:
    std::unordered_map<std::string, Symbol*> symbols;

public:
    SymbolTable() {

        // built-in types
        defineVar("int", "builtin", "global");
        defineVar("void", "builtin", "global");

        // built-in functions
        defineFunc("input", "int", 0);
        defineFunc("output", "void", 1);
    }

    ~SymbolTable() {
        symbols.clear();
    }

    Symbol* get(std::string symbolName, std::string scopeName) {
        return symbols[scopeName + symbolName];
    }

    void set(std::string symbolName, std::string scopeName, Symbol* symbol) {
        symbols[scopeName + symbolName] = symbol;
    }

    void defineVar(std::string symbolName, std::string symbolType,
                   std::string scopeName) {
        set(symbolName, scopeName,
            new Symbol(symbolName, symbolType, scopeName, false));
    }

    void defineFunc(std::string symbolName, std::string symbolType,
                    int symbolNumArgs) {
        set(symbolName, "global",
            new Symbol(symbolName, symbolType, symbolNumArgs, true));
    }

    bool contains(std::string symbolName, std::string scopeName) {
        return symbols.find(scopeName + symbolName) != symbols.end();
    }

    std::string getScope(std::string symbolName, std::string scopeName) {
        if (contains(symbolName, scopeName)) {
            return get(symbolName, scopeName)->getScopeName();
        } else {
            return "";
        }
    }

    int getNumArgs(std::string symbolName, std::string scopeName) {
        if (contains(symbolName, "global")) {
            return get(symbolName, "global")->getNumArgs();
        } else {
            return 0;
        }
    }

    std::string dump() {
        std::stringstream oss;
        for (auto const& pair : symbols) {
            oss << pair.second->toString() << "\n";
        }
        return oss.str();
    }
};

#endif
