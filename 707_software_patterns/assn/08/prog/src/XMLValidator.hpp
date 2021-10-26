#ifndef XML_VALIDATOR_HPP
#define XML_VALIDATOR_HPP

#include <fstream>
#include <ios>
#include <string>
#include <vector>

#include "Element.hpp"
// #include "Observer.hpp"
#include "Subject.hpp"
#include "ValidChildren.hpp"

class ValidChildren;
class Subject;

class XMLValidator {
private:
    std::vector<ValidChildren*> schema;
    Subject* subject;

public:
    XMLValidator() : subject(0) {}
    XMLValidator(Subject* _subject) : subject(_subject) {}
    ~XMLValidator();

    virtual ValidChildren* addSchemaElement(std::string);
    virtual std::vector<ValidChildren*>::iterator
        findSchemaElement(std::string);
    virtual bool canRootElement(std::string);
    virtual bool canAddElement(dom::Element*, std::string);
    virtual bool canAddText(dom::Element*);
    virtual bool canAddAttribute(dom::Element*, std::string);

    virtual void shareValidationInfo(std::string&, const std::string&, bool);
};

#endif
