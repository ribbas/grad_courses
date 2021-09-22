#ifndef NODE_H
#define NODE_H

#include "NodeList.hpp"
#include <string>

namespace dom {
class Document;

class Node {
public:
    static const short ATTRIBUTE_NODE = 0;
    static const short DOCUMENT_NODE = 1;
    static const short ELEMENT_NODE = 2;
    static const short TEXT_NODE = 3;

    virtual ~Node() {}

    // virtual const std::string& getNodeName() = 0;
    // virtual const std::string& getNodeValue() = 0;
    // virtual void setNodeValue(const std::string&) = 0;
    // virtual short getNodeType() = 0;
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
    // virtual const std::string& getLocalName() = 0;
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
};
}; // namespace dom

class Node_Impl : public virtual dom::Node {
private:
    // std::string name;
    // std::string value;
    // short nodeType;
    dom::Node* parent;
    dom::NodeList nodes;

    dom::Node* getSibling(int);

protected:
    dom::Document* document;

    Node_Impl();

public:
    virtual ~Node_Impl();

    // virtual const std::string& getNodeName();
    // virtual const std::string& getNodeValue();
    // virtual void setNodeValue(const std::string&);
    // virtual short getNodeType();
    virtual dom::Node* getParentNode();
    virtual dom::NodeList* getChildNodes();
    virtual dom::Node* getFirstChild();
    virtual dom::Node* getLastChild();
    virtual dom::Node* getPreviousSibling();
    virtual dom::Node* getNextSibling();
    virtual dom::Document* getOwnerDocument();
    virtual dom::Node* insertBefore(dom::Node*, dom::Node*);
    virtual dom::Node* replaceChild(dom::Node*, dom::Node*);
    virtual dom::Node* removeChild(dom::Node*);
    virtual dom::Node* appendChild(dom::Node*);
    virtual bool hasChildNodes();
    // virtual const std::string& getLocalName();

    virtual void setParent(dom::Node*);
};

#endif // NODE_H
