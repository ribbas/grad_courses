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
private:
    std::vector<ValidChildren*> schema;

public:
    XMLValidator() {}
    ~XMLValidator() {
        for (int i = 0; i < schema.size(); i++)
            delete schema[i];
    }

    virtual ValidChildren* addSchemaElement(std::string);
    virtual std::vector<ValidChildren*>::iterator
        findSchemaElement(std::string);
    virtual bool canRootElement(std::string);
    virtual bool canAddElement(dom::Element*, std::string);
    virtual bool canAddText(dom::Element*);
    virtual bool canAddAttribute(dom::Element*, std::string);
};
