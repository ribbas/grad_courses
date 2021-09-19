#ifndef ATTR_H
#define ATTR_H

#include <string>

#include "Node.hpp"

namespace dom {
class Document;
class Element;

class Attr : public virtual Node {
public:
    virtual ~Attr() {}

    virtual const std::string& getName() = 0;
    virtual const std::string& getValue() = 0;
    virtual void setValue(const std::string&) = 0;
    virtual Element* getOwnerElement() = 0;
};
}; // namespace dom

class Attr_Impl : public virtual dom::Attr, Node_Impl {
protected:
    Attr_Impl(const std::string&, dom::Document*);
    Attr_Impl(const std::string&, const std::string&, dom::Document*);

public:
    friend class Document_Impl;
    friend class Element_Impl;

    virtual ~Attr_Impl();

    virtual const std::string& getName();
    virtual const std::string& getValue();
    virtual void setValue(const std::string&);
    virtual dom::Element* getOwnerElement();
};

#endif // ATTR_H
