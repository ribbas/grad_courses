#ifndef DOM_DOCUMENT_ADAPTER_HPP
#define DOM_DOCUMENT_ADAPTER_HPP

#include "NodeAdapter.hpp"

class DocumentAdapter : public virtual XERCES::DOMDocument {
private:
    dom::Document* adaptee;

public:
    DocumentAdapter();
    DocumentAdapter(dom::Document*);

    virtual XERCES::DOMElement* createElement(const XERCES::XMLCh*);
    virtual XERCES::DOMText* createTextNode(const XERCES::XMLCh*);
    virtual XERCES::DOMAttr* createAttribute(const XERCES::XMLCh*);
    virtual XERCES::DOMElement* getDocumentElement() const;

    virtual XERCES::DOMNode* getParentNode() const;
    virtual XERCES::DOMNode* getFirstChild() const;
    virtual XERCES::DOMNode* getLastChild() const;
    virtual XERCES::DOMNode* getPreviousSibling() const;
    virtual XERCES::DOMNode* getNextSibling() const;
    virtual XERCES::DOMNode* insertBefore(XERCES::DOMNode*, XERCES::DOMNode*);
    virtual XERCES::DOMNode* replaceChild(XERCES::DOMNode*, XERCES::DOMNode*);
    virtual XERCES::DOMNode* removeChild(XERCES::DOMNode*);
    virtual XERCES::DOMNode* appendChild(XERCES::DOMNode*);

    virtual const XERCES::XMLCh* getNodeName() const;
    virtual const XERCES::XMLCh* getNodeValue() const;
    virtual XERCES::DOMNode::NodeType getNodeType() const;
    virtual XERCES::DOMNodeList* getChildNodes() const;
    virtual XERCES::DOMDocument* getOwnerDocument() const;
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
    virtual XERCES::DOMDocumentFragment* createDocumentFragment();
    virtual XERCES::DOMComment* createComment(const XERCES::XMLCh*);
    virtual XERCES::DOMCDATASection* createCDATASection(const XERCES::XMLCh*);
    virtual XERCES::DOMProcessingInstruction*
    createProcessingInstruction(const XERCES::XMLCh*, const XERCES::XMLCh*);
    virtual XERCES::DOMEntityReference*
    createEntityReference(const XERCES::XMLCh*);
    virtual XERCES::DOMDocumentType* getDoctype() const;
    virtual XERCES::DOMImplementation* getImplementation() const;
    virtual XERCES::DOMNodeList*
    getElementsByTagName(const XERCES::XMLCh*) const;
    virtual XERCES::DOMNode* importNode(const XERCES::DOMNode*, bool);
    virtual XERCES::DOMElement* createElementNS(const XERCES::XMLCh*,
                                                const XERCES::XMLCh*);
    virtual XERCES::DOMAttr* createAttributeNS(const XERCES::XMLCh*,
                                               const XERCES::XMLCh*);
    virtual XERCES::DOMNodeList*
    getElementsByTagNameNS(const XERCES::XMLCh*, const XERCES::XMLCh*) const;
    virtual XERCES::DOMElement* getElementById(const XERCES::XMLCh*) const;
    virtual const XERCES::XMLCh* getInputEncoding() const;
    virtual const XERCES::XMLCh* getXmlEncoding() const;
    virtual bool getXmlStandalone() const;
    virtual void setXmlStandalone(bool);
    virtual const XERCES::XMLCh* getXmlVersion() const;
    virtual void setXmlVersion(const XERCES::XMLCh*);
    virtual const XERCES::XMLCh* getDocumentURI() const;
    virtual void setDocumentURI(const XERCES::XMLCh*);
    virtual bool getStrictErrorChecking() const;
    virtual void setStrictErrorChecking(bool);
    virtual XERCES::DOMNode* renameNode(XERCES::DOMNode*, const XERCES::XMLCh*,
                                        const XERCES::XMLCh*);
    virtual XERCES::DOMNode* adoptNode(XERCES::DOMNode*);
    virtual void normalizeDocument();
    virtual XERCES::DOMConfiguration* getDOMConfig() const;
    virtual XERCES::DOMEntity* createEntity(const XERCES::XMLCh*);
    virtual XERCES::DOMDocumentType* createDocumentType(const XERCES::XMLCh*);
    virtual XERCES::DOMNotation* createNotation(const XERCES::XMLCh*);
    virtual XERCES::DOMElement* createElementNS(const XERCES::XMLCh*,
                                                const XERCES::XMLCh*,
                                                const XERCES::XMLFileLoc,
                                                const XERCES::XMLFileLoc);
};

#endif
