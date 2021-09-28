#include "ValidChildren.hpp"

ValidChildren::ValidChildren(std::string _thisElement)
    : thisElement(_thisElement), _canHaveText(false) {}

ValidChildren::~ValidChildren() {}

std::string ValidChildren::getThisElement() {
    return thisElement;
}

bool ValidChildren::canHaveText() {
    return _canHaveText;
}

void ValidChildren::setCanHaveText(bool __canHaveText) {
    _canHaveText = __canHaveText;
}

void ValidChildren::addValidChild(const std::string& child, bool isAttribute) {

    if (childIsValid(child, isAttribute)) {
        return;
    }

    validChildren.push_back(child);
    childIsAttribute.push_back(isAttribute);
}

bool ValidChildren::childIsValid(const std::string& child, bool isAttribute) {

    for (unsigned int i = 0; i < validChildren.size(); i++) {

        if (childIsAttribute[i] == isAttribute &&
            validChildren[i].compare(child) == 0) {
            return true;
        }
    }

    return false;
}