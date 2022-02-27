#ifndef SYMTAB_HPP
#define SYMTAB_HPP

#include <string>
#include <unordered_map>

class Symbol {        // A generic programming language symbol
    std::string name; // All symbols at least have a name
    std::string type;

public:
    Symbol(std::string name) {
        name = name;
    }

    Symbol(std::string name, std::string type) {
        name = name;
        type = type;
    }

    std::string getName() {
        return name;
    }

    std::string toString() {
        if (type.length()) {
            return '<' + getName() + ":" + type + '>';
        }
        return getName();
    }
};

class VariableSymbol : public Symbol {
public:
    VariableSymbol(std::string name, std::string type) : Symbol(name, type) {}
};

class BuiltInTypeSymbol : public Symbol {
public:
    BuiltInTypeSymbol(std::string name) : Symbol(name) {}
};

class SymbolTable { // single-scope symtab
private:
    std::unordered_map<std::string, Symbol*> symbols;

protected:
    void initTypeSystem() {
        define(new BuiltInTypeSymbol("int"));
    }

public:
    SymbolTable() {
        initTypeSystem();
    }

    // Satisfy Scope interface
public:
    void define(Symbol* sym) {
        symbols[sym->getName()] = sym;
    }

    Symbol* resolve(std::string name) {
        return symbols[name];
    }

    // std::string toString() {
    //     return symbols;
    // }
};

#endif
