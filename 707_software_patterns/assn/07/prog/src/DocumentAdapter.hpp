#ifndef DOM_DOCUMENT_ADAPTER_HPP
#define DOM_DOCUMENT_ADAPTER_HPP

#include "NodeAdapter.hpp"

namespace XERCES {

class DocumentAdapter : public virtual DOMDocument {
private:
    dom::Document* adaptee;

public:
    DocumentAdapter();
    DocumentAdapter(dom::Document*);
    virtual ~DocumentAdapter();

    virtual DOMElement* createElement(const XMLCh*);
    virtual DOMText* createTextNode(const XMLCh*);
    virtual DOMAttr* createAttribute(const XMLCh*);
    virtual DOMElement* getDocumentElement() const;
    virtual DOMNode* getParentNode() const;
    virtual DOMNode* getFirstChild() const;
    virtual DOMNode* getLastChild() const;
    virtual DOMNode* getPreviousSibling() const;
    virtual DOMNode* getNextSibling() const;
    virtual DOMNode* insertBefore(DOMNode*, DOMNode*);
    virtual DOMNode* replaceChild(DOMNode*, DOMNode*);
    virtual DOMNode* removeChild(DOMNode*);
    virtual DOMNode* appendChild(DOMNode*);
    virtual const XMLCh* getNodeName() const;
    virtual const XMLCh* getNodeValue() const;
    virtual DOMNode::NodeType getNodeType() const;
    virtual DOMNodeList* getChildNodes() const;
    virtual DOMDocument* getOwnerDocument() const;
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
    virtual DOMDocumentFragment* createDocumentFragment();
    virtual DOMComment* createComment(const XMLCh*);
    virtual DOMCDATASection* createCDATASection(const XMLCh*);
    virtual DOMProcessingInstruction* createProcessingInstruction(const XMLCh*,
                                                                  const XMLCh*);
    virtual DOMEntityReference* createEntityReference(const XMLCh*);
    virtual DOMDocumentType* getDoctype() const;
    virtual DOMImplementation* getImplementation() const;
    virtual DOMNodeList* getElementsByTagName(const XMLCh*) const;
    virtual DOMNode* importNode(const DOMNode*, bool);
    virtual DOMElement* createElementNS(const XMLCh*, const XMLCh*);
    virtual DOMAttr* createAttributeNS(const XMLCh*, const XMLCh*);
    virtual DOMNodeList* getElementsByTagNameNS(const XMLCh*,
                                                const XMLCh*) const;
    virtual DOMElement* getElementById(const XMLCh*) const;
    virtual const XMLCh* getInputEncoding() const;
    virtual const XMLCh* getXmlEncoding() const;
    virtual bool getXmlStandalone() const;
    virtual void setXmlStandalone(bool);
    virtual const XMLCh* getXmlVersion() const;
    virtual void setXmlVersion(const XMLCh*);
    virtual const XMLCh* getDocumentURI() const;
    virtual void setDocumentURI(const XMLCh*);
    virtual bool getStrictErrorChecking() const;
    virtual void setStrictErrorChecking(bool);
    virtual DOMNode* renameNode(DOMNode*, const XMLCh*, const XMLCh*);
    virtual DOMNode* adoptNode(DOMNode*);
    virtual void normalizeDocument();
    virtual DOMConfiguration* getDOMConfig() const;
    virtual DOMEntity* createEntity(const XMLCh*);
    virtual DOMDocumentType* createDocumentType(const XMLCh*);
    virtual DOMNotation* createNotation(const XMLCh*);
    virtual DOMElement* createElementNS(const XMLCh*, const XMLCh*,
                                        const XMLFileLoc, const XMLFileLoc);
};
}; // namespace XERCES

#endif
