#include "XMLInterpreter.hpp"
#include <algorithm>

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

            numOpands++;
            if (numOpands == 1) {
                result = std::stod(currentTerm);
            } else {
                opand2 = std::stod(currentTerm);
            }

        } else {

            if (currentTerm == "+") {
                if (numOpands == 2) {
                    result += opand2;
                }
            } else if (currentTerm == "-") {
                if (numOpands == 2) {
                    result = opand2 - result;
                } else if (numOpands == 1) {
                    result = -result;
                }
            } else if (currentTerm == "*") {
                if (numOpands == 2) {
                    result *= opand2;
                }
            } else if (currentTerm == "/") {
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
