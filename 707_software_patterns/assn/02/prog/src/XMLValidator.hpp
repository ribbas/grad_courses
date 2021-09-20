#include <fstream>
#include <ios>
#include <string>
#include <vector>

#include "Element.hpp"

class ValidChildren {
private:
    std::string thisElement;
    std::vector<std::string> validChildren;
    std::vector<bool> childIsAttribute;
    bool _canHaveText;

public:
    ValidChildren(std::string _thisElement)
        : thisElement(_thisElement), _canHaveText(false) {}

    virtual std::string getThisElement() {
        return thisElement;
    }
    virtual bool canHaveText() {
        return _canHaveText;
    }
    virtual void setCanHaveText(bool __canHaveText) {
        _canHaveText = __canHaveText;
    }

    virtual void addValidChild(const std::string&, bool);
    virtual bool childIsValid(const std::string&, bool);
};

class XMLValidator {
protected:
    std::vector<ValidChildren*> schema;
    dom::Element* element_;

public:
    XMLValidator() {}
    ~XMLValidator() {
        for (int i = 0; i < schema.size(); i++) {
            delete schema[i];
        }
    }

    void setElement(dom::Element* element) {
        element_ = element;
    }

    virtual ValidChildren* addSchemaElement(std::string);
    virtual std::vector<ValidChildren*>::iterator
        findSchemaElement(std::string);
};

class ElementComponent : public XMLValidator {

public:
    ElementComponent() {}
    bool validate(std::string newElement) {

        std::vector<ValidChildren*>::iterator schemaElement =
            findSchemaElement(element_ == 0 ? "" : element_->getTagName());

        return schemaElement == schema.end()
                   ? true
                   : (*schemaElement)->childIsValid(newElement, false);
    }
};

class AttrComponent : public XMLValidator {

public:
    AttrComponent() {}
    bool validate(std::string newAttribute) {

        std::vector<ValidChildren*>::iterator schemaElement =
            findSchemaElement(element_->getTagName());

        return schemaElement == schema.end()
                   ? true
                   : (*schemaElement)->childIsValid(newAttribute, true);
    }
};

class TextComponent : public XMLValidator {

public:
    TextComponent() {}
    bool validate() {

        std::vector<ValidChildren*>::iterator schemaElement =
            findSchemaElement(element_->getTagName());

        return schemaElement == schema.end() ? true
                                             : (*schemaElement)->canHaveText();
    }
};
