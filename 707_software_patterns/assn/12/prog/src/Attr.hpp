#ifndef ATTR_HPP
#define ATTR_HPP

#include "Node.hpp"
#include <string>

namespace dom {
class Document;
class Element;

class Attr : public virtual Node {
public:
    virtual const std::string& getName() = 0;
    virtual const std::string& getValue() = 0;
    virtual void setValue(const std::string&) = 0;
    virtual Element* getOwnerElement() = 0;
    // virtual void serialize(std::fstream*, WhitespaceStrategy*) = 0;
};
}; // namespace dom

class Attr_Impl : public virtual dom::Attr, Node_Impl {
protected:
    Attr_Impl(const std::string&, dom::Document*);
    Attr_Impl(const std::string&, const std::string&, dom::Document*);
    virtual ~Attr_Impl();

public:
    friend class Document_Impl;
    friend class Element_Impl;

    virtual const std::string& getName() override;
    virtual const std::string& getValue() override;
    virtual void setValue(const std::string&) override;
    virtual dom::Element* getOwnerElement() override;
    // virtual void serialize(std::fstream*, WhitespaceStrategy*) override;
    virtual void accept(XMLVisitor*) override;

    virtual Node* insertBefore(Node*, Node*) override;
    virtual Node* replaceChild(Node*, Node*) override;
    virtual Node* removeChild(Node*) override;
    virtual Node* appendChild(Node*) override;
};

#endif // ATTR_HPP
