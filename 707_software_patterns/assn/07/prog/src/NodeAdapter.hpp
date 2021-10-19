#ifndef DOM_NODE_ADAPTER_HPP
#define DOM_NODE_ADAPTER_HPP

#include "DOMDocument.hpp"
#include "DOMNode.hpp"
#include "Document.hpp"
#include "Node.hpp"

class NodeAdapter : public virtual XERCES::DOMNode {
private:
    dom::Node* adaptee;

public:
    NodeAdapter(const std::string&, short, dom::Document*);
    NodeAdapter(dom::Node*);

    virtual const XERCES::XMLCh* getNodeName() const;
    virtual const XERCES::XMLCh* getNodeValue() const;
    virtual XERCES::DOMNode::NodeType getNodeType() const;
    virtual XERCES::DOMNode* getParentNode() const;
    virtual XERCES::DOMNodeList* getChildNodes() const;
    virtual XERCES::DOMNode* getFirstChild() const;
    virtual XERCES::DOMNode* getLastChild() const;
    virtual XERCES::DOMNode* getPreviousSibling() const;
    virtual XERCES::DOMNode* getNextSibling() const;
    virtual XERCES::DOMDocument* getOwnerDocument() const;
    virtual XERCES::DOMNode* insertBefore(XERCES::DOMNode*, XERCES::DOMNode*);
    virtual XERCES::DOMNode* replaceChild(XERCES::DOMNode*, XERCES::DOMNode*);
    virtual XERCES::DOMNode* removeChild(XERCES::DOMNode*);
    virtual XERCES::DOMNode* appendChild(XERCES::DOMNode*);
    virtual bool hasChildNodes() const;
    virtual void setNodeValue(const XERCES::XMLCh*);

    virtual XERCES::DOMNamedNodeMap* getAttributes() const;
    virtual XERCES::DOMNode* cloneNode(bool) const;
    virtual void normalize();
    virtual bool isSupported(const XERCES::XMLCh*, const XERCES::XMLCh*) const;
    virtual const XERCES::XMLCh* getNamespaceURI() const;
    virtual const XERCES::XMLCh* getPrefix() const;
    virtual const XERCES::XMLCh* getLocalName() const;
    virtual void setPrefix(const XERCES::XMLCh*);
    virtual bool hasAttributes() const;
    virtual bool isSameNode(const XERCES::DOMNode*) const;
    virtual bool isEqualNode(const XERCES::DOMNode*) const;
    virtual void* setUserData(const XERCES::XMLCh*, void*,
                              XERCES::DOMUserDataHandler*);
    virtual void* getUserData(const XERCES::XMLCh*) const;
    virtual const XERCES::XMLCh* getBaseURI() const;
    virtual short compareDocumentPosition(const XERCES::DOMNode*) const;
    virtual const XERCES::XMLCh* getTextContent() const;
    virtual void setTextContent(const XERCES::XMLCh*);
    virtual const XERCES::XMLCh* lookupPrefix(const XERCES::XMLCh*) const;
    virtual bool isDefaultNamespace(const XERCES::XMLCh*) const;
    virtual const XERCES::XMLCh* lookupNamespaceURI(const XERCES::XMLCh*) const;
    virtual void* getFeature(const XERCES::XMLCh*, const XERCES::XMLCh*) const;
    virtual void release();
};

#endif
