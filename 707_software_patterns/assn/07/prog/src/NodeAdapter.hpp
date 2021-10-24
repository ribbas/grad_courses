#ifndef DOM_NODE_ADAPTER_HPP
#define DOM_NODE_ADAPTER_HPP

#include "DOMDocument.hpp"
#include "DOMNode.hpp"
#include "Document.hpp"
#include "Node.hpp"

namespace XERCES {

class NodeAdapter : public virtual DOMNode {
private:
    dom::Node* adaptee;

public:
    NodeAdapter(const std::string&, short, dom::Document*);
    NodeAdapter(dom::Node*);
    virtual ~NodeAdapter();

    virtual const XMLCh* getNodeName() const;
    virtual const XMLCh* getNodeValue() const;
    virtual DOMNode::NodeType getNodeType() const;
    virtual DOMNode* getParentNode() const;
    virtual DOMNodeList* getChildNodes() const;
    virtual DOMNode* getFirstChild() const;
    virtual DOMNode* getLastChild() const;
    virtual DOMNode* getPreviousSibling() const;
    virtual DOMNode* getNextSibling() const;
    virtual DOMDocument* getOwnerDocument() const;
    virtual DOMNode* insertBefore(DOMNode*, DOMNode*);
    virtual DOMNode* replaceChild(DOMNode*, DOMNode*);
    virtual DOMNode* removeChild(DOMNode*);
    virtual DOMNode* appendChild(DOMNode*);
    virtual bool hasChildNodes() const;
    virtual void setNodeValue(const XMLCh*);
    virtual DOMNamedNodeMap* getAttributes() const;

    // empty methods since they have yet to be implemented
    virtual DOMNode* cloneNode(bool) const;
    virtual void normalize();
    virtual bool isSupported(const XMLCh*, const XMLCh*) const;
    virtual const XMLCh* getNamespaceURI() const;
    virtual const XMLCh* getPrefix() const;
    virtual const XMLCh* getLocalName() const;
    virtual void setPrefix(const XMLCh*);
    virtual bool hasAttributes() const;
    virtual bool isSameNode(const DOMNode*) const;
    virtual bool isEqualNode(const DOMNode*) const;
    virtual void* setUserData(const XMLCh*, void*, DOMUserDataHandler*);
    virtual void* getUserData(const XMLCh*) const;
    virtual const XMLCh* getBaseURI() const;
    virtual short compareDocumentPosition(const DOMNode*) const;
    virtual const XMLCh* getTextContent() const;
    virtual void setTextContent(const XMLCh*);
    virtual const XMLCh* lookupPrefix(const XMLCh*) const;
    virtual bool isDefaultNamespace(const XMLCh*) const;
    virtual const XMLCh* lookupNamespaceURI(const XMLCh*) const;
    virtual void* getFeature(const XMLCh*, const XMLCh*) const;
    virtual void release();
};
}; // namespace XERCES

#endif
