#ifndef SYMTAB_HPP
#define SYMTAB_HPP

#include <iostream>
#include <string>
#include <unordered_map>

class Symbol { // A generic programming language symbol

    std::string name; // All symbols at least have a name
    std::string type;

public:
    Symbol(std::string _name) {
        name = _name;
    }

    Symbol(std::string _name, std::string _type) {
        name = _name;
        type = _type;
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

    // protected:
    //     void initTypeSystem() {
    //         add(new BuiltInTypeSymbol("int"));
    //     }

public:
    SymbolTable() {
        // initTypeSystem();
    }

public:
    void add(std::string symbolName) {
        symbols[symbolName] = new Symbol(symbolName);
    }

    void add(std::string symbolName, std::string symbolType) {
        symbols[symbolName] = new VariableSymbol(symbolName, symbolType);
    }

    void dump() {
        for (auto const& pair : symbols) {
            std::cout << pair.second->toString() << "\n";
        }
    }

    void add(Symbol* sym) {
        symbols[sym->getName()] = sym;
    }

    std::string resolve(std::string name) {
        std::cout << "resplving " << name << '\n';
        // if (symbols[name]) {
        //     return symbols[name]->toString();
        // }
    }
};

#endif
