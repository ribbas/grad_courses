#include "XMLValidator.hpp"

XMLValidator::XMLValidator() {}

XMLValidator::~XMLValidator() {
    for (unsigned int i = 0; i < schema.size(); i++) {
        delete schema[i];
    }
    while (!history.empty()) {
        history.pop();
    }
}

ValidChildren* XMLValidator::addSchemaElement(std::string element) {
    std::vector<ValidChildren*>::iterator schemaElementIterator =
        findSchemaElement(element);

    if (schemaElementIterator != schema.end()) {
        schema.erase(schemaElementIterator);
        delete *schemaElementIterator;
    }

    ValidChildren* schemaElement = 0;
    schema.push_back(schemaElement = new ValidChildren(element));
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

XMLValidator::Memento::Memento() {}

XMLValidator::Memento::~Memento() {}

XMLValidator::Memento* XMLValidator::createMemento() {
    XMLValidator::Memento* memento = new XMLValidator::Memento();
    memento->schema = cloneSchema(this->schema);
    return memento;
}

std::vector<ValidChildren*>
XMLValidator::cloneSchema(const std::vector<ValidChildren*>& oldSchema) {

    std::vector<ValidChildren*> clonedSchema;
    for (unsigned int i = 0; i < oldSchema.size(); i++) {
        ValidChildren* clonedValidChildren = new ValidChildren(*oldSchema[i]);
        clonedSchema.push_back(clonedValidChildren);
    }
    return clonedSchema;
}

void XMLValidator::setMemento(XMLValidator::Memento* memento) {

    for (unsigned int i = 0; i < schema.size(); i++) {
        delete schema[i];
    }

    schema = XMLValidator::cloneSchema(memento->schema);
}

void XMLValidator::save() {
    history.push(createMemento());
}

void XMLValidator::undo() {
    XMLValidator::Memento* lastSave = history.top();
    setMemento(lastSave);
    history.pop();
}
