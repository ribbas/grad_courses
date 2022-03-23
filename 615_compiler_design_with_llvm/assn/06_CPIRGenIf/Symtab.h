#ifndef SYMTAB_H
#define SYMTAB_H

#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>

class Symbol {
private:
    std::string name;
    std::string type;
    std::string scope;
    bool isFunc;
    int numArgs;
    int size;
    int value;

public:
    Symbol(std::string _name, std::string _type, std::string scope, int _size)
        : name(_name), type(_type), scope(scope), isFunc(false), numArgs(-1),
          size(_size), value(-1) {}

    Symbol(std::string _name, std::string _type, int _numArgs, bool _isFunc)
        : name(_name), type(_type), scope("global"), isFunc(_isFunc),
          numArgs(_numArgs), size(-1), value(-1) {}

    void setType(std::string _type) {
        type = _type;
    }

    void setScope(std::string scopeName) {
        scope = scopeName;
    }

    void setIsFunc(bool _isFunc) {
        isFunc = _isFunc;
    }

    void setNumArgs(int _numArgs) {
        numArgs = _numArgs;
    }

    void setSize(int _size) {
        size = _size;
    }

    void setValue(int _value) {
        value = _value;
    }

    std::string getScope() {
        return scope;
    }

    std::string getType() {
        return type;
    }

    bool getIsFunc() {
        return isFunc;
    }

    int getNumArgs() {
        return numArgs;
    }

    int getSize() {
        return size;
    }

    int getValue() {
        return value;
    }

    std::string toString() {
        if (isFunc) {
            return "<name:" + name + "><type:" + type +
                   "><func><narg:" + std::to_string(numArgs) + '>';
        } else {
            // if variable is not an array
            if (size == -1) {
                return "<name:" + name + "><type:" + type +
                       "><var><value:" + std::to_string(value) + '>';
            } else {
                return "<name:" + name + "><type:" + type +
                       "><var><size:" + std::to_string(size) + '>';
            }
        }
    }
};

class SymbolTable {
private:
    std::unordered_map<std::string, Symbol*> symbols;
    std::set<std::string> scopeList = {"global"};

    Symbol* get(std::string symbolName, std::string scopeName) {
        return symbols[scopeName + symbolName];
    }

    void set(std::string symbolName, std::string scopeName, Symbol* symbol) {
        scopeList.insert(scopeName);
        symbols[scopeName + symbolName] = symbol;
    }

public:
    SymbolTable() {

        // built-in types
        defineType("int");
        defineType("void");

        // built-in functions
        defineFunc("input", "int", 0);
        defineFunc("output", "void", 1);
    }

    ~SymbolTable() {
        symbols.clear();
    }

    void defineType(std::string symbolName) {
        set(symbolName, "global",
            new Symbol(symbolName, "builtin", "global", -1));
    }

    void defineVar(std::string symbolName, std::string symbolType,
                   std::string scopeName, int size) {
        set(symbolName, scopeName,
            new Symbol(symbolName, symbolType, scopeName, size));
    }

    void defineFunc(std::string symbolName, std::string symbolType,
                    int symbolNumArgs) {
        set(symbolName, "global",
            new Symbol(symbolName, symbolType, symbolNumArgs, true));
    }

    bool contains(std::string symbolName, std::string scopeName) {
        if (symbols.find(scopeName + symbolName) == symbols.end()) {
            if (symbols.find("global" + symbolName) == symbols.end()) {
                return false;
            }
        }
        return true;
    }

    std::string getScope(std::string symbolName, std::string scopeName) {
        if (contains(symbolName, scopeName)) {
            return get(symbolName, scopeName)->getScope();
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

        // a very inefficient way to dump the symtab with the scopes in order
        std::stringstream oss;
        for (auto s = scopeList.begin(); s != scopeList.end(); ++s) {
            oss << "<scope:" << *s << ">\n";
            for (auto const& pair : symbols) {
                if (pair.second->getScope() == *s) {
                    oss << '\t' << pair.second->toString() << "\n";
                }
            }
        }
        return oss.str();
    }
};

#endif
