#ifndef SYMTAB_HPP
#define SYMTAB_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

class Symbol { // A generic programming language symbol

    std::string name; // All symbols at least have a name
    std::string type = "builtin";

public:
    Symbol(std::string _name) {
        name = _name;
    }

    Symbol(std::string _name, std::string _type) {
        name = _name;
        type = _type;
    }

    std::string toString() {
        if (type.length()) {
            return '<' + name + ":" + type + '>';
        }
        return name;
    }
};

class SymbolTable { // single-scope symtab
private:
    std::unordered_map<std::string, Symbol*> symbols;

public:
    SymbolTable() {}

    void define(std::string symbolName) {
        symbols[symbolName] = new Symbol(symbolName);
    }

    void define(std::string symbolName, std::string symbolType) {
        symbols[symbolName] = new Symbol(symbolName, symbolType);
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
