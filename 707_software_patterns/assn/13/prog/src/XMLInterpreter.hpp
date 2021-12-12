#ifndef XML_INTERPRETER_HPP
#define XML_INTERPRETER_HPP

#include "Element.hpp"
#include "Text.hpp"
#include <stack>
#include <string>

class XMLInterpreter {
private:
    std::stack<std::string> terms;

    bool isNumber(const std::string&);

public:
    XMLInterpreter();
    ~XMLInterpreter();
    void interpret(dom::Element*);
    double eval();
};

#endif // XML_INTERPRETER_HPP
