#ifndef SYMTAB_HPP
#define SYMTAB_HPP

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
    Symbol(std::string _name) : name(_name) {}

    Symbol(std::string _name, std::string _type) : name(_name), type(_type) {}

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
        define("int");
        define("void");

        // built-in functions
        define("input", "int", 0, true);
        define("output", "void", 1, true);
    }

    void setNumArgs(std::string symbolName, int numArgs) {
        if (contains(symbolName)) {
            symbols[symbolName]->setNumArgs(numArgs);
        }
    }

    void define(std::string symbolName) {
        symbols[symbolName] = new Symbol(symbolName);
    }

    void define(std::string symbolName, std::string symbolType) {
        symbols[symbolName] = new Symbol(symbolName, symbolType);
    }

    void define(std::string symbolName, std::string symbolType,
                int symbolNumArgs, bool isFunc) {
        symbols[symbolName] =
            new Symbol(symbolName, symbolType, symbolNumArgs, isFunc);
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
