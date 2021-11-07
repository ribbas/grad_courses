#ifndef VALID_CHILDREN_HPP
#define VALID_CHILDREN_HPP

#include <string>
#include <vector>

class ValidChildren {
private:
    std::string thisElement;
    std::vector<std::string> validChildren;
    std::vector<bool> childIsAttribute;
    bool _canHaveText;

public:
    ValidChildren(std::string);
    virtual ~ValidChildren();

    virtual std::string getThisElement();
    virtual bool canHaveText();
    virtual void setCanHaveText(bool);
    virtual void addValidChild(const std::string&, bool);
    virtual bool childIsValid(const std::string&, bool);
};

#endif // VALID_CHILDREN_HPP