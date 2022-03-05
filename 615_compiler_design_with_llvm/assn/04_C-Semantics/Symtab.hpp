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

public:
    Symbol(std::string _name) : name(_name) {}

    Symbol(std::string _name, std::string _type) : name(_name), type(_type) {}

    void setNumArgs(int _numArgs) {
        numArgs = _numArgs;
    }

    std::string getType() {
        return type;
    }

    std::string toString() {
        if (type.length()) {
            // std::cout << "args " << name << " " << numArgs << "\n";
            return '<' + name + ":" + type + '>';
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
        define("input", "int");
        define("output", "void");
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

    bool contains(std::string symbolName) {
        return symbols.find(symbolName) != symbols.end();
    }

    std::string getType(std::string symbolName) {
        if (contains(symbolName)) {
            return symbols[symbolName]->getType();
        } else {
            return "";
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
