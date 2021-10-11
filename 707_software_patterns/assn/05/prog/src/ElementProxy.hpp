#ifndef ELEMENT_PROXY_H
#define ELEMENT_PROXY_H

#include "Element.hpp"
#include "XMLDirector.hpp"

class ElementProxy : public virtual dom::Element, public virtual Node_Impl {
private:
    dom::Element* realSubject;
    const std::string& tagName;
    dom::Document* document;
    XMLDirector* director;
    bool realized;
    int streamPos;

    void realize();

public:
    ElementProxy(const std::string&, dom::Document*);
    virtual ~ElementProxy();

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
    virtual void serialize(std::fstream*, WhitespaceStrategy*) override;

    /* Proxy helper methods */
    dom::Element* getRealSubject();
    void setStreamPos(int);
    void setDirector(XMLDirector*);

    /* Methods that need the real object instantiated */
    virtual dom::Node* appendChild(dom::Node*) override;
    virtual dom::Document* getOwnerDocument() override;
    virtual dom::NodeList* getChildNodes() override;
    virtual dom::Node* getFirstChild() override;
    virtual dom::Node* getLastChild() override;
    virtual bool hasChildNodes() override;
};

#endif
