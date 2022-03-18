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

public:
    Symbol(std::string _name, std::string _type, bool _isFunc)
        : name(_name), type(_type), isFunc(_isFunc) {}

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

    std::string toString() {
        if (type.length()) {
            return "<name:" + name + ", type:" + type + ", " +
                   (isFunc ? "func" : "var") +
                   ", narg:" + std::to_string(numArgs) + '>';
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
        define("int", "builtin");
        define("void", "builtin");

        // built-in functions
        define("input", "int", 0);
        define("output", "void", 1);
    }

    ~SymbolTable() {
        symbols.clear();
    }

    void setNumArgs(std::string symbolName, int numArgs) {
        if (contains(symbolName)) {
            symbols[symbolName]->setNumArgs(numArgs);
        }
    }

    void define(std::string symbolName, std::string symbolType) {
        symbols[symbolName] = new Symbol(symbolName, symbolType, false);
    }

    void define(std::string symbolName, std::string symbolType,
                int symbolNumArgs) {
        symbols[symbolName] =
            new Symbol(symbolName, symbolType, symbolNumArgs, true);
    }

    bool contains(std::string symbolName) {
        return symbols.find(symbolName) != symbols.end();
    }

    bool isFunc(std::string symbolName) {
        if (contains(symbolName)) {
            return symbols[symbolName]->getIsFunc();
        } else {
            return false;
        }
    }

    std::string getType(std::string symbolName) {
        if (contains(symbolName)) {
            return symbols[symbolName]->getType();
        } else {
            return "";
        }
    }

    int getNumArgs(std::string symbolName) {
        if (contains(symbolName)) {
            return symbols[symbolName]->getNumArgs();
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
