#ifndef XML_VALIDATOR_HPP
#define XML_VALIDATOR_HPP

#include <fstream>
#include <ios>
#include <string>
#include <vector>

#include "Element.hpp"
#include "Subject.hpp"
#include "ValidChildren.hpp"

class XMLValidator : public virtual Observer {
private:
    std::vector<ValidChildren*> schema;
    Subject* subject;

public:
    XMLValidator() : subject(nullptr) {}
    XMLValidator(Subject* _subject) : subject(_subject) {}
    virtual ~XMLValidator();

    virtual ValidChildren* addSchemaElement(std::string);
    virtual std::vector<ValidChildren*>::iterator
        findSchemaElement(std::string);
    virtual bool canRootElement(std::string);
    virtual bool canAddElement(dom::Element*, std::string);
    virtual bool canAddText(dom::Element*);
    virtual bool canAddAttribute(dom::Element*, std::string);

    // Observer functions
    virtual void update(Subject*);

    virtual void getValidationStatus(const std::string&, bool);
};

#endif
