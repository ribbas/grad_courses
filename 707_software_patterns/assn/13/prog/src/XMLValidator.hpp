#ifndef XML_VALIDATOR_H
#define XML_VALIDATOR_H

#include "Element.hpp"
#include "ValidChildren.hpp"
#include <fstream>

class XMLValidator {
private:
    std::vector<ValidChildren*> schema;

public:
    XMLValidator() {}
    ~XMLValidator();

    virtual ValidChildren* addSchemaElement(std::string);
    virtual std::vector<ValidChildren*>::iterator
        findSchemaElement(std::string);
    virtual bool canRootElement(std::string);
    virtual bool canAddElement(dom::Element*, std::string);
    virtual bool canAddText(dom::Element*);
    virtual bool canAddAttribute(dom::Element*, std::string);
};

#endif
