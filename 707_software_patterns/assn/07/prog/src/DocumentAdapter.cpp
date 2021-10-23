#include "DocumentAdapter.hpp"

DocumentAdapter::DocumentAdapter() : adaptee(new Document_Impl()) {}
DocumentAdapter::DocumentAdapter(dom::Document* adaptee) : adaptee(adaptee) {}

DocumentAdapter::~DocumentAdapter() {
    if (adaptee) {
        delete adaptee;
    }
}

XERCES::DOMElement*
DocumentAdapter::createElement(const XERCES::XMLCh* /* tagName */) {
    // once the DOMElement class is implemented, the following can
    // instead be returned:
    // new
    // Element(dynamic_cast<dom::Document*>(adaptee)->createElement(tagName));
    return nullptr;
}

XERCES::DOMText*
DocumentAdapter::createTextNode(const XERCES::XMLCh* /* data */) {
    // once the DOMText class is implemented, the following can
    // instead be returned:
    // new Text(dynamic_cast<dom::Document*>(adaptee)->createTextNode(data));
    return nullptr;
}

XERCES::DOMAttr*
DocumentAdapter::createAttribute(const XERCES::XMLCh* /* name */) {
    // once the DOMAttr class is implemented, the following can
    // instead be returned:
    // new Attr(dynamic_cast<dom::Document*>(adaptee)->createAttribute(name));
    return nullptr;
}

XERCES::DOMElement* DocumentAdapter::getDocumentElement() const {
    // once the DOMElement class is implemented, the following can
    // instead be returned:
    // new Element(dynamic_cast<dom::Document*>(adaptee)->getDocumentElement());
    return nullptr;
}

XERCES::DOMNode* DocumentAdapter::getParentNode() const {
    return dynamic_cast<XERCES::DOMNode*>(adaptee->getParentNode());
}

XERCES::DOMNode* DocumentAdapter::getFirstChild() const {
    return dynamic_cast<XERCES::DOMNode*>(adaptee->getFirstChild());
}

XERCES::DOMNode* DocumentAdapter::getLastChild() const {
    return dynamic_cast<XERCES::DOMNode*>(adaptee->getLastChild());
}

XERCES::DOMNode* DocumentAdapter::getPreviousSibling() const {
    return dynamic_cast<XERCES::DOMNode*>(adaptee->getPreviousSibling());
}

XERCES::DOMNode* DocumentAdapter::getNextSibling() const {
    return dynamic_cast<XERCES::DOMNode*>(adaptee->getNextSibling());
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
    return adaptee->getNodeName().c_str();
}

const XERCES::XMLCh* DocumentAdapter::getNodeValue() const {
    return adaptee->getNodeValue().c_str();
}

XERCES::DOMNode::NodeType DocumentAdapter::getNodeType() const {
    switch (adaptee->getNodeType()) {
        case dom::Node::ATTRIBUTE_NODE:
            return XERCES::DOMNode::ATTRIBUTE_NODE;
        case dom::Node::DOCUMENT_NODE:
            return XERCES::DOMNode::DOCUMENT_NODE;
        case dom::Node::ELEMENT_NODE:
            return XERCES::DOMNode::ELEMENT_NODE;
        case dom::Node::TEXT_NODE:
            return XERCES::DOMNode::TEXT_NODE;
        default:
            return (XERCES::DOMNode::NodeType)(0);
    }
}

XERCES::DOMNodeList* DocumentAdapter::getChildNodes() const {
    return nullptr;
}

XERCES::DOMDocument* DocumentAdapter::getOwnerDocument() const {
    return nullptr;
}

bool DocumentAdapter::hasChildNodes() const {
    return adaptee->hasChildNodes();
}

void DocumentAdapter::setNodeValue(const XERCES::XMLCh* nodeValue) {
    adaptee->setNodeValue(nodeValue);
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
