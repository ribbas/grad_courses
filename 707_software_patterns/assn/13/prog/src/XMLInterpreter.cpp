#include "XMLInterpreter.hpp"

XMLInterpreter::XMLInterpreter() {}

XMLInterpreter::~XMLInterpreter() {
    while (terms.size()) {
        terms.pop();
    }
}

bool XMLInterpreter::isNumber(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) {
                             return !std::isdigit(c);
                         }) == s.end();
}

void XMLInterpreter::interpret(dom::Element* element) {

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

double XMLInterpreter::eval() {

    double result = 0.0;
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
