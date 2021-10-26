#ifndef VALIDCHILDREN_HPP
#define VALIDCHILDREN_HPP

#include <string>
#include <vector>

#include "Observer.hpp"

class XMLValidator;

class ValidChildren : public Observer {
private:
    std::string thisElement;
    std::vector<std::string> validChildren;
    std::vector<bool> childIsAttribute;
    bool _canHaveText;
    XMLValidator* mediator;
    bool active;

public:
    ValidChildren(std::string _thisElement, XMLValidator* _mediator)
        : thisElement(_thisElement), _canHaveText(false), mediator(_mediator),
          active(true) {}

    virtual ~ValidChildren();

    virtual std::string getThisElement();
    virtual bool canHaveText();
    virtual void setCanHaveText(bool);

    virtual void addValidChild(const std::string&, bool);
    virtual bool childIsValid(const std::string&, bool);

    virtual void activate() {
        active = true;
    }
    virtual void deactivate() {
        active = false;
    }
    virtual bool update(dom::Node* container, short targetType,
                        std::string& target);

    void shareValidationInfo(const std::string&, bool) {}
};

#endif // VALIDCHILDREN_H