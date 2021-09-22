#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

#include "DocumentNode.hpp"
#include "NamedNodeMap.hpp"

namespace dom {
class Attr;
class NodeList;
class Document;

class Element : public virtual DocumentNode {
public:
    virtual ~Element() {}

    virtual const std::string& getAttribute(const std::string&) = 0;
    virtual Attr* getAttributeNode(const std::string&) = 0;
    virtual NodeList* getElementsByTagName(const std::string&) = 0;
    virtual bool hasAttribute(const std::string&) = 0;
    virtual void removeAttribute(const std::string&) = 0;
    virtual Attr* removeAttributeNode(Attr*) = 0;
    virtual void setAttribute(const std::string&, const std::string&) = 0;
    virtual Attr* setAttributeNode(Attr*) = 0;

    virtual dom::NamedNodeMap* getAttributes() = 0;
    virtual bool hasAttributes() = 0;
};
}; // namespace dom

class Element_Impl : public virtual dom::Element,
                     public virtual DocumentNode_Impl {
private:
    NamedNodeMap_Impl attributes;

protected:
    Element_Impl(const std::string&, dom::Document*);

public:
    friend class Document_Impl;

    virtual ~Element_Impl();

    virtual const std::string& getAttribute(const std::string&);
    virtual dom::Attr* getAttributeNode(const std::string&);
    virtual dom::NodeList* getElementsByTagName(const std::string&);
    virtual bool hasAttribute(const std::string&);
    virtual void removeAttribute(const std::string&);
    virtual dom::Attr* removeAttributeNode(dom::Attr*);
    virtual void setAttribute(const std::string&, const std::string&);
    virtual dom::Attr* setAttributeNode(dom::Attr*);

    virtual dom::NamedNodeMap* getAttributes() {
        return &attributes;
    }
    virtual bool hasAttributes() {
        return attributes.size() > 0;
    }
};

#endif // ELEMENT_H
