#ifndef NODE_HPP
#define NODE_HPP

#include "DOMException.hpp"
#include "Flyweight.hpp"
#include "NodeList.hpp"
#include "WhitespaceStrategy.hpp"
#include <string>

namespace dom {

class Document;
class Element;
class Attr;
class Text;

class Node {

public:
    static const short ATTRIBUTE_NODE = 0;
    static const short DOCUMENT_NODE = 1;
    static const short ELEMENT_NODE = 2;
    static const short TEXT_NODE = 3;

    virtual ~Node() {}
    virtual const std::string& getNodeName() = 0;
    virtual const std::string& getNodeValue() = 0;
    virtual void setNodeValue(const std::string&) = 0;
    virtual short getNodeType() = 0;
    virtual Node* getParentNode() = 0;
    virtual NodeList* getChildNodes() = 0;
    virtual Node* getFirstChild() = 0;
    virtual Node* getLastChild() = 0;
    virtual Node* getPreviousSibling() = 0;
    virtual Node* getNextSibling() = 0;
    virtual Document* getOwnerDocument() = 0;
    virtual Node* insertBefore(Node*, Node*) = 0;
    virtual Node* replaceChild(Node*, Node*) = 0;
    virtual Node* removeChild(Node*) = 0;
    virtual Node* appendChild(Node*) = 0;
    virtual bool hasChildNodes() = 0;
    virtual const std::string& getLocalName() = 0;
    virtual void serialize(std::fstream*, WhitespaceStrategy*) = 0;
};

}; // namespace dom

class Node_Impl : public virtual dom::Node {
private:
    dom::Node* parent;
    dom::NodeList nodes;

    dom::Node* getSibling(int);

protected:
    dom::Flyweight* sharedStates;

    Node_Impl(const std::string&, short, dom::Document*);

public:
    virtual ~Node_Impl();
    virtual const std::string& getNodeName() override;
    virtual const std::string& getNodeValue() override;
    virtual void setNodeValue(const std::string&) override;
    virtual short getNodeType() override;
    virtual dom::Node* getParentNode() override;
    virtual dom::NodeList* getChildNodes() override;
    virtual dom::Node* getFirstChild() override;
    virtual dom::Node* getLastChild() override;
    virtual dom::Node* getPreviousSibling() override;
    virtual dom::Node* getNextSibling() override;
    virtual dom::Document* getOwnerDocument() override;
    virtual dom::Node* insertBefore(dom::Node*, dom::Node*) override;
    virtual dom::Node* replaceChild(dom::Node*, dom::Node*) override;
    virtual dom::Node* removeChild(dom::Node*) override;
    virtual dom::Node* appendChild(dom::Node*) override;
    virtual bool hasChildNodes() override;
    virtual const std::string& getLocalName() override;
    virtual void setParent(dom::Node*);
};

#endif // NODE_HPP
