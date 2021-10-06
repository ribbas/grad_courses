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

    //
    // Serialization Data Extraction Strategy
    //
    virtual void serialize(std::fstream*, WhitespaceStrategy*) = 0;

    virtual const std::string& getAttribute(const std::string&) = 0;
    virtual Attr* getAttributeNode(const std::string&) = 0;
    virtual NodeList* getElementsByTagName(const std::string&) = 0;
    virtual const std::string& getTagName() = 0;
    virtual bool hasAttribute(const std::string&) = 0;
    virtual void removeAttribute(const std::string&) = 0;
    virtual Attr* removeAttributeNode(Attr*) = 0;
    virtual void setAttribute(const std::string&, const std::string&) = 0;
    virtual Attr* setAttributeNode(Attr*) = 0;

    virtual dom::NamedNodeMap* getAttributes() = 0;
    virtual bool hasAttributes() = 0;
};
}; // namespace dom

class Element_Impl : public virtual dom::Element, public virtual Node_Impl {
private:
    NamedNodeMap_Impl attributes;

protected:
    Element_Impl(const std::string&, dom::Document*);

public:
    friend class Document_Impl;

    virtual ~Element_Impl();

    //
    // Serialization Data Extraction Strategy
    //
    virtual void serialize(std::fstream*, WhitespaceStrategy*) override;

    virtual const std::string& getAttribute(const std::string&) override;
    virtual dom::Attr* getAttributeNode(const std::string&) override;
    virtual dom::NodeList* getElementsByTagName(const std::string&) override;
    virtual const std::string& getTagName() override;
    virtual bool hasAttribute(const std::string&) override;
    virtual void removeAttribute(const std::string&) override;
    virtual dom::Attr* removeAttributeNode(dom::Attr*) override;
    virtual void setAttribute(const std::string&, const std::string&) override;
    virtual dom::Attr* setAttributeNode(dom::Attr*) override;

    virtual dom::NamedNodeMap* getAttributes() override;
    virtual bool hasAttributes() override;
};

#endif // ELEMENT_H
