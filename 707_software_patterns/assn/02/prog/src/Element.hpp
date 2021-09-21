#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

#include "NamedNodeMap.hpp"
#include "Node.hpp"

namespace dom {
class Attr;
class NodeList;
class Document;

class Element : public virtual Node {
public:
    virtual ~Element() {}

    virtual const std::string& getAttribute(const std::string& name) = 0;
    virtual Attr* getAttributeNode(const std::string& name) = 0;
    virtual NodeList* getElementsByTagName(const std::string& tagName) = 0;
    virtual const std::string& getTagName() = 0;
    virtual bool hasAttribute(const std::string& name) = 0;
    virtual void removeAttribute(const std::string& name) = 0;
    virtual Attr* removeAttributeNode(Attr* oldAttr) = 0;
    virtual void setAttribute(const std::string& name,
                              const std::string& value) = 0;
    virtual Attr* setAttributeNode(Attr* newAttr) = 0;

    virtual dom::NamedNodeMap* getAttributes() = 0;
    virtual bool hasAttributes() = 0;
};
}; // namespace dom

class Element_Impl : public virtual dom::Element, Node_Impl {
private:
    NamedNodeMap_Impl attributes;

protected:
    Element_Impl(const std::string&, dom::Document*);

public:
    friend class Document_Impl;
    friend class DocumentNodeFactory;

    virtual ~Element_Impl();

    virtual const std::string& getAttribute(const std::string&);
    virtual dom::Attr* getAttributeNode(const std::string&);
    virtual dom::NodeList* getElementsByTagName(const std::string&);
    virtual const std::string& getTagName();
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
