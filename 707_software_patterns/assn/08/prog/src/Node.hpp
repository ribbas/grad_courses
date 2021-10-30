#ifndef NODE_HPP
#define NODE_HPP

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

class DOMException {
private:
    int reason;
    std::string description;

public:
    DOMException(int r, const std::string& d) : reason(r), description(d) {}

    virtual ~DOMException() {}

    int getReason() {
        return reason;
    }
    const std::string& getDescription() {
        return description;
    }

    static const int WRONG_DOCUMENT_ERR = 0;
    static const int INUSE_ATTRIBUTE_ERR = 1;
    static const int INDEX_SIZE_ERR = 2;
    static const int NOT_FOUND_ERR = 3;
    static const int NO_MODIFICATION_ALLOWED_ERR = 4;
    static const int INVALID_CHARACTER_ERR = 5;
    static const int HIERARCHY_REQUEST_ERR = 6;
    static const int VALIDATION_ERR = 7;
};

}; // namespace dom

class Node_Impl : public virtual dom::Node {
private:
    std::string name;
    std::string value;
    short nodeType;
    dom::Node* parent;
    dom::NodeList nodes;

    dom::Node* getSibling(int);

protected:
    dom::Document* document;

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
