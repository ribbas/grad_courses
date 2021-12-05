#ifndef XML_INTERPRETER_HPP
#define XML_INTERPRETER_HPP

#include "Element.hpp"
#include "Text.hpp"
#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

class XMLInterpreter {
private:
    std::string expression;
    std::stack<std::string> terms;
    double result;

public:
    XMLInterpreter() : result(0.0) {}
    ~XMLInterpreter() {}

    bool isNumber(const std::string& s) {
        return !s.empty() &&
               std::find_if(s.begin(), s.end(), [](unsigned char c) {
                   return !std::isdigit(c);
               }) == s.end();
    }

    void interpret(dom::Element* element) {
        std::string tagName = element->getTagName();
        if (tagName == "operation") {
            terms.push(element->getAttribute("type"));
        } else if (tagName == "value") {
            for (dom::NodeList::iterator it = element->getChildNodes()->begin();
                 it != element->getChildNodes()->end(); it++) {
                if (dynamic_cast<dom::Text*>(*it.operator->())) {
                    terms.push((*it)->getNodeValue());
                }
            }
        }
    }

    double eval() {

        double opand2 = 0.0;
        int numOpands = 0;
        std::string currentTerm;

        while (terms.size()) {

            currentTerm = terms.top();

            if (isNumber(currentTerm)) {

                std::cout << "LITERAL " << currentTerm << '\n';
                numOpands++;
                if (numOpands == 1) {
                    result = std::stod(currentTerm);
                } else {
                    opand2 = std::stod(currentTerm);
                }

            } else {
                if (currentTerm == "+") {
                    // std::cout << "ADD " << currentTerm << '\n';
                    if (numOpands == 2) {
                        result += opand2;
                    }
                } else if (currentTerm == "-") {
                    // std::cout << "SUB " << currentTerm << '\n';
                    if (numOpands == 2) {
                        result = opand2 - result;
                    } else if (numOpands == 1) {
                        result = -result;
                    }
                } else if (currentTerm == "*") {
                    // std::cout << "MUL " << currentTerm << '\n';
                    if (numOpands == 2) {
                        result *= opand2;
                    }
                } else if (currentTerm == "/") {
                    // std::cout << "DIV " << terms.top() << '\n';
                    if (numOpands == 2) {
                        result = opand2 / result;
                    }
                }
                numOpands = 1;
            }
            terms.pop();
        }

        return result;
    }
};

#endif // DOM_INTERPRETER_HPP
