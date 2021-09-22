#ifndef ATTR_H
#define ATTR_H

#include <string>

#include "DocumentNode.hpp"

namespace dom {
class Document;
class Element;

class Attr : public virtual DocumentNode {
public:
    virtual ~Attr() {}

    virtual Element* getOwnerElement() = 0;
};
}; // namespace dom

class Attr_Impl : public virtual dom::Attr, public virtual DocumentNode_Impl {
protected:
    Attr_Impl(const std::string& tagName, dom::Document* document);
    Attr_Impl(const std::string& tagName, const std::string& value,
              dom::Document* document);

public:
    friend class Document_Impl;
    friend class Element_Impl;

    virtual ~Attr_Impl();

    virtual dom::Element* getOwnerElement();
};

#endif // ATTR_H
