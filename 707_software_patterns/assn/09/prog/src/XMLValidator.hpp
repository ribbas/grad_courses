#ifndef XML_VALIDATOR_HPP
#define XML_VALIDATOR_HPP

#include "Element.hpp"
#include "ValidChildren.hpp"
#include <fstream>
#include <stack>

class XMLValidator {
private:
    class Memento {
    private:
        friend class XMLValidator;
        std::vector<ValidChildren*> schema;

        Memento();
    };

    std::stack<XMLValidator::Memento*> history;
    std::vector<ValidChildren*> schema;

    virtual Memento* createMemento();
    std::vector<ValidChildren*> cloneSchema(const std::vector<ValidChildren*>&);
    virtual void setMemento(Memento*);

public:
    XMLValidator();
    ~XMLValidator();

    virtual ValidChildren* addSchemaElement(std::string);
    virtual std::vector<ValidChildren*>::iterator
        findSchemaElement(std::string);
    virtual bool canRootElement(std::string);
    virtual bool canAddElement(dom::Element*, std::string);
    virtual bool canAddText(dom::Element*);
    virtual bool canAddAttribute(dom::Element*, std::string);

    virtual void save();
    virtual void revertToLastSave();
};

#endif // XML_VALIDATOR_HPP
