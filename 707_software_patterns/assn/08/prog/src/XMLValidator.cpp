#include "XMLValidator.hpp"

XMLValidator::~XMLValidator() {
    for (unsigned int i = 0; i < schema.size(); i++) {
        delete schema[i];
    }
}

ValidChildren* XMLValidator::addSchemaElement(std::string element) {
    std::vector<ValidChildren*>::iterator schemaElementIterator =
        findSchemaElement(element);

    if (schemaElementIterator != schema.end()) {
        schema.erase(schemaElementIterator);
        if (subject != 0) {
            subject->detach(*schemaElementIterator);
        }
        delete *schemaElementIterator;
    }

    ValidChildren* schemaElement = 0;
    schema.push_back(schemaElement = new ValidChildren(element, this));
    if (subject != 0)
        subject->attach(schemaElement);
    return schemaElement;
}

std::vector<ValidChildren*>::iterator
XMLValidator::findSchemaElement(std::string element) {
    for (std::vector<ValidChildren*>::iterator i = schema.begin();
         i != schema.end(); i++) {
        if (((*i)->getThisElement().size() == 0 && element.size() == 0) ||
            ((*i)->getThisElement().size() > 0 &&
             (*i)->getThisElement().compare(element) == 0)) {
            return i;
        }
    }

    return schema.end();
}

bool XMLValidator::canRootElement(std::string newElement) {
    return canAddElement(0, newElement);
}

bool XMLValidator::canAddElement(dom::Element* element,
                                 std::string newElement) {
    std::vector<ValidChildren*>::iterator schemaElement =
        findSchemaElement(element == 0 ? "" : element->getTagName());

    return schemaElement == schema.end()
               ? true
               : (*schemaElement)->childIsValid(newElement, false);
}

bool XMLValidator::canAddText(dom::Element* element) {
    std::vector<ValidChildren*>::iterator schemaElement =
        findSchemaElement(element->getTagName());

    return schemaElement == schema.end() ? true
                                         : (*schemaElement)->canHaveText();
}

bool XMLValidator::canAddAttribute(dom::Element* element,
                                   std::string newAttribute) {
    std::vector<ValidChildren*>::iterator schemaElement =
        findSchemaElement(element->getTagName());

    return schemaElement == schema.end()
               ? true
               : (*schemaElement)->childIsValid(newAttribute, true);
}

void XMLValidator::shareValidationInfo(const std::string& child, bool isValid) {

    for (ValidChildren* schemaElement : schema) {
        schemaElement->shareValidationInfo(child, isValid);
    }

    // if (isAttribute && thisElement == "element" && child == "attribute")
    //     for (std::vector<ValidChildren*>::iterator i = schema.begin();
    //          i != schema.end(); i++) {
    //         (*i)->deactivate();
    //     }
}