#ifndef DOCUMENT_COMPONENT_H
#define DOCUMENT_COMPONENT_H

#include <string>

#include "NamedNodeMap.hpp"
#include "Node.hpp"

namespace dom {

class DocumentNode : public virtual Node {
public:
    virtual ~DocumentNode() {}
    virtual const std::string& getNodeName() = 0;
    virtual const std::string& getNodeValue() = 0;
    virtual void setNodeValue(const std::string&) = 0;
    virtual short getNodeType() = 0;
};
}; // namespace dom

class DocumentNode_Impl : public virtual dom::DocumentNode, public Node_Impl {
private:
    std::string name;
    std::string value;
    short nodeType;

protected:
    DocumentNode_Impl(const std::string& n, short type, dom::Document* document)
        : name(n), value(""), nodeType(type) {
        Node_Impl::document = document;
    }

public:
    virtual ~DocumentNode_Impl() {}

    const std::string& getNodeName() {
        return name;
    }

    const std::string& getNodeValue() {
        return value;
    }

    void setNodeValue(const std::string& nodeValue) {
        value = nodeValue;
    }

    short getNodeType() {
        return nodeType;
    }
};

#endif // DocumentNode
