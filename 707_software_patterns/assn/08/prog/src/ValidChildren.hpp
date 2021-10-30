#ifndef VALIDCHILDREN_HPP
#define VALIDCHILDREN_HPP

#include "Observer.hpp"
#include <string>
#include <vector>

class XMLValidator;

class ValidChildren {
private:
    std::string thisElement;
    std::vector<std::string> validChildren;
    std::vector<bool> childIsAttribute;
    bool _canHaveText;
    XMLValidator* mediator;

public:
    ValidChildren(std::string, XMLValidator*);
    virtual ~ValidChildren();

    virtual std::string getThisElement();
    virtual bool canHaveText();
    virtual void setCanHaveText(bool);
    virtual void addValidChild(const std::string&, bool);
    virtual bool childIsValid(const std::string&, bool);

    // Mediator method
    void getValidationStatus(const std::string&, bool);
};

#endif // VALIDCHILDREN_H