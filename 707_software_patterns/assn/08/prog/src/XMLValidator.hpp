#ifndef XML_VALIDATOR_HPP
#define XML_VALIDATOR_HPP

#include "Element.hpp"
#include "Subject.hpp"
#include "ValidChildren.hpp"

class XMLValidator : public virtual Observer {
private:
    std::vector<ValidChildren*> schema;
    Subject* subject;

public:
    XMLValidator();
    virtual ~XMLValidator();

    virtual ValidChildren* addSchemaElement(std::string);
    virtual std::vector<ValidChildren*>::iterator
        findSchemaElement(std::string);
    virtual bool canRootElement(std::string);
    virtual bool canAddElement(dom::Element*, std::string);
    virtual bool canAddText(dom::Element*);
    virtual bool canAddAttribute(dom::Element*, std::string);

    // Observer method
    virtual void update(Subject*);

    // Mediator method
    virtual void getValidationStatus(const std::string&, bool);
};

#endif // XML_VALIDATOR_HPP
