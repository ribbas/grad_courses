#include "DocumentAdapter.hpp"

DocumentAdapter::DocumentAdapter() : NodeAdapter(new Document_Impl()) {}
DocumentAdapter::DocumentAdapter(dom::Document* adaptee)
    : NodeAdapter(adaptee) {}

XERCES::DOMElement*
DocumentAdapter::createElement(const XERCES::XMLCh* tagName) {
    // return new Element(
    //     dynamic_cast<dom::Document*>(getAdaptee())->createElement(tagName));
    return nullptr;
}

XERCES::DOMText* DocumentAdapter::createTextNode(const XERCES::XMLCh* data) {
    // return new Text(
    //     dynamic_cast<dom::Document*>(getAdaptee())->createTextNode(data));
    return nullptr;
}

XERCES::DOMAttr* DocumentAdapter::createAttribute(const XERCES::XMLCh* name) {
    // return new Attr(
    //     dynamic_cast<dom::Document*>(getAdaptee())->createAttribute(name));
    return nullptr;
}

XERCES::DOMElement* DocumentAdapter::getDocumentElement() const {
    // return new Element(
    //     dynamic_cast<dom::Document*>(getAdaptee())->getDocumentElement());
    return nullptr;
}

XERCES::DOMNode* DocumentAdapter::getParentNode() const {
    return dynamic_cast<XERCES::DOMDocument*>(new DocumentAdapter(
        dynamic_cast<dom::Document*>(const_cast<DocumentAdapter*>(this)
                                         ->getAdaptee()
                                         ->getParentNode())));
}

XERCES::DOMNode* DocumentAdapter::getFirstChild() const {
    return dynamic_cast<XERCES::DOMDocument*>(new DocumentAdapter(
        dynamic_cast<dom::Document*>(const_cast<DocumentAdapter*>(this)
                                         ->getAdaptee()
                                         ->getFirstChild())));
}

XERCES::DOMNode* DocumentAdapter::getLastChild() const {
    return dynamic_cast<XERCES::DOMDocument*>(
        new DocumentAdapter(dynamic_cast<dom::Document*>(
            const_cast<DocumentAdapter*>(this)->getAdaptee()->getLastChild())));
}

XERCES::DOMNode* DocumentAdapter::getPreviousSibling() const {
    return dynamic_cast<XERCES::DOMDocument*>(new DocumentAdapter(
        dynamic_cast<dom::Document*>(const_cast<DocumentAdapter*>(this)
                                         ->getAdaptee()
                                         ->getPreviousSibling())));
}

XERCES::DOMNode* DocumentAdapter::getNextSibling() const {
    return dynamic_cast<XERCES::DOMDocument*>(new DocumentAdapter(
        dynamic_cast<dom::Document*>(const_cast<DocumentAdapter*>(this)
                                         ->getAdaptee()
                                         ->getNextSibling())));
}

XERCES::DOMNode* DocumentAdapter::insertBefore(XERCES::DOMNode*,
                                               XERCES::DOMNode*) {
    return nullptr;
}

XERCES::DOMNode* DocumentAdapter::replaceChild(XERCES::DOMNode*,
                                               XERCES::DOMNode*) {
    return nullptr;
}

XERCES::DOMNode* DocumentAdapter::removeChild(XERCES::DOMNode*) {
    return nullptr;
}

XERCES::DOMNode* DocumentAdapter::appendChild(XERCES::DOMNode*) {
    return nullptr;
}

const XERCES::XMLCh* DocumentAdapter::getNodeName() const {
    return NodeAdapter::getNodeName();
}
const XERCES::XMLCh* DocumentAdapter::getNodeValue() const {
    return NodeAdapter::getNodeValue();
}
XERCES::DOMNode::NodeType DocumentAdapter::getNodeType() const {
    return NodeAdapter::getNodeType();
}
XERCES::DOMNodeList* DocumentAdapter::getChildNodes() const {
    return NodeAdapter::getChildNodes();
}
XERCES::DOMDocument* DocumentAdapter::getOwnerDocument() const {
    return NodeAdapter::getOwnerDocument();
}
bool DocumentAdapter::hasChildNodes() const {
    return NodeAdapter::hasChildNodes();
}
void DocumentAdapter::setNodeValue(const XERCES::XMLCh* nodeValue) {
    NodeAdapter::setNodeValue(nodeValue);
}

XERCES::DOMNamedNodeMap* DocumentAdapter::getAttributes() const {
    return nullptr;
}
XERCES::DOMNode* DocumentAdapter::cloneNode(bool) const {
    return nullptr;
}
void DocumentAdapter::normalize() {}
bool DocumentAdapter::isSupported(const XERCES::XMLCh*,
                                  const XERCES::XMLCh*) const {
    return false;
}
const XERCES::XMLCh* DocumentAdapter::getNamespaceURI() const {
    return nullptr;
}
const XERCES::XMLCh* DocumentAdapter::getPrefix() const {
    return nullptr;
}
const XERCES::XMLCh* DocumentAdapter::getLocalName() const {
    return nullptr;
}
void DocumentAdapter::setPrefix(const XERCES::XMLCh*) {}
bool DocumentAdapter::hasAttributes() const {
    return false;
}
bool DocumentAdapter::isSameNode(const XERCES::DOMNode*) const {
    return false;
}
bool DocumentAdapter::isEqualNode(const XERCES::DOMNode*) const {
    return false;
}
void* DocumentAdapter::setUserData(const XERCES::XMLCh*, void*,
                                   XERCES::DOMUserDataHandler*) {
    return nullptr;
}
void* DocumentAdapter::getUserData(const XERCES::XMLCh*) const {
    return nullptr;
}
const XERCES::XMLCh* DocumentAdapter::getBaseURI() const {
    return nullptr;
}
short DocumentAdapter::compareDocumentPosition(const XERCES::DOMNode*) const {
    return 0;
}
const XERCES::XMLCh* DocumentAdapter::getTextContent() const {
    return nullptr;
}
void DocumentAdapter::setTextContent(const XERCES::XMLCh*) {}
const XERCES::XMLCh* DocumentAdapter::lookupPrefix(const XERCES::XMLCh*) const {
    return nullptr;
}
bool DocumentAdapter::isDefaultNamespace(const XERCES::XMLCh*) const {
    return false;
}
const XERCES::XMLCh*
DocumentAdapter::lookupNamespaceURI(const XERCES::XMLCh*) const {
    return nullptr;
}
void* DocumentAdapter::getFeature(const XERCES::XMLCh*,
                                  const XERCES::XMLCh*) const {
    return nullptr;
}
void DocumentAdapter::release() {}
//
// No implementation for these.
//
XERCES::DOMDocumentFragment* DocumentAdapter::createDocumentFragment() {
    return nullptr;
}
XERCES::DOMComment* DocumentAdapter::createComment(const XERCES::XMLCh*) {
    return nullptr;
}
XERCES::DOMCDATASection*
DocumentAdapter::createCDATASection(const XERCES::XMLCh*) {
    return nullptr;
}
XERCES::DOMProcessingInstruction*
DocumentAdapter::createProcessingInstruction(const XERCES::XMLCh*,
                                             const XERCES::XMLCh*) {
    return nullptr;
}
XERCES::DOMEntityReference*
DocumentAdapter::createEntityReference(const XERCES::XMLCh*) {
    return nullptr;
}
XERCES::DOMDocumentType* DocumentAdapter::getDoctype() const {
    return nullptr;
}
XERCES::DOMImplementation* DocumentAdapter::getImplementation() const {
    return nullptr;
}
XERCES::DOMNodeList*
DocumentAdapter::getElementsByTagName(const XERCES::XMLCh*) const {
    return nullptr;
}
XERCES::DOMNode* DocumentAdapter::importNode(const XERCES::DOMNode*, bool) {
    return nullptr;
}
XERCES::DOMElement* DocumentAdapter::createElementNS(const XERCES::XMLCh*,
                                                     const XERCES::XMLCh*) {
    return nullptr;
}
XERCES::DOMAttr* DocumentAdapter::createAttributeNS(const XERCES::XMLCh*,
                                                    const XERCES::XMLCh*) {
    return nullptr;
}
XERCES::DOMNodeList*
DocumentAdapter::getElementsByTagNameNS(const XERCES::XMLCh*,
                                        const XERCES::XMLCh*) const {
    return nullptr;
}
XERCES::DOMElement*
DocumentAdapter::getElementById(const XERCES::XMLCh*) const {
    return nullptr;
}
const XERCES::XMLCh* DocumentAdapter::getInputEncoding() const {
    return nullptr;
}
const XERCES::XMLCh* DocumentAdapter::getXmlEncoding() const {
    return nullptr;
}
bool DocumentAdapter::getXmlStandalone() const {
    return false;
}
void DocumentAdapter::setXmlStandalone(bool) {}
const XERCES::XMLCh* DocumentAdapter::getXmlVersion() const {
    return nullptr;
}

void DocumentAdapter::setXmlVersion(const XERCES::XMLCh*) {}

const XERCES::XMLCh* DocumentAdapter::getDocumentURI() const {
    return nullptr;
}
void DocumentAdapter::setDocumentURI(const XERCES::XMLCh*) {}
bool DocumentAdapter::getStrictErrorChecking() const {
    return false;
}
void DocumentAdapter::setStrictErrorChecking(bool) {}
XERCES::DOMNode* DocumentAdapter::renameNode(XERCES::DOMNode*,
                                             const XERCES::XMLCh*,
                                             const XERCES::XMLCh*) {
    return nullptr;
}
XERCES::DOMNode* DocumentAdapter::adoptNode(XERCES::DOMNode*) {
    return nullptr;
}
void DocumentAdapter::normalizeDocument() {}
XERCES::DOMConfiguration* DocumentAdapter::getDOMConfig() const {
    return nullptr;
}
XERCES::DOMEntity* DocumentAdapter::createEntity(const XERCES::XMLCh*) {
    return nullptr;
}
XERCES::DOMDocumentType*
DocumentAdapter::createDocumentType(const XERCES::XMLCh*) {
    return nullptr;
}
XERCES::DOMNotation* DocumentAdapter::createNotation(const XERCES::XMLCh*) {
    return nullptr;
}
XERCES::DOMElement* DocumentAdapter::createElementNS(const XERCES::XMLCh*,
                                                     const XERCES::XMLCh*,
                                                     const XERCES::XMLFileLoc,
                                                     const XERCES::XMLFileLoc) {
    return nullptr;
}