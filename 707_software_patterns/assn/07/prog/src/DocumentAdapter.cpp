#include "DocumentAdapter.hpp"

using namespace XERCES;

DocumentAdapter::DocumentAdapter() : adaptee(new Document_Impl()) {}

DocumentAdapter::DocumentAdapter(dom::Document* adaptee) : adaptee(adaptee) {}

DocumentAdapter::~DocumentAdapter() {
    if (adaptee) {
        delete adaptee;
    }
}

DOMElement* DocumentAdapter::createElement(const XMLCh* /* tagName */) {
    // once the DOMElement class is implemented, the following can
    // instead be returned:
    // new
    // Element(dynamic_cast<dom::Document*>(adaptee)->createElement(tagName));
    return nullptr;
}

DOMText* DocumentAdapter::createTextNode(const XMLCh* /* data */) {
    // once the DOMText class is implemented, the following can
    // instead be returned:
    // new Text(dynamic_cast<dom::Document*>(adaptee)->createTextNode(data));
    return nullptr;
}

DOMAttr* DocumentAdapter::createAttribute(const XMLCh* /* name */) {
    // once the DOMAttr class is implemented, the following can
    // instead be returned:
    // new Attr(dynamic_cast<dom::Document*>(adaptee)->createAttribute(name));
    return nullptr;
}

DOMElement* DocumentAdapter::getDocumentElement() const {
    // once the DOMElement class is implemented, the following can
    // instead be returned:
    // new Element(dynamic_cast<dom::Document*>(adaptee)->getDocumentElement());
    return nullptr;
}

DOMNode* DocumentAdapter::getParentNode() const {
    return dynamic_cast<DOMNode*>(adaptee->getParentNode());
}

DOMNode* DocumentAdapter::getFirstChild() const {
    return dynamic_cast<DOMNode*>(adaptee->getFirstChild());
}

DOMNode* DocumentAdapter::getLastChild() const {
    return dynamic_cast<DOMNode*>(adaptee->getLastChild());
}

DOMNode* DocumentAdapter::getPreviousSibling() const {
    return dynamic_cast<DOMNode*>(adaptee->getPreviousSibling());
}

DOMNode* DocumentAdapter::getNextSibling() const {
    return dynamic_cast<DOMNode*>(adaptee->getNextSibling());
}

DOMNode* DocumentAdapter::insertBefore(DOMNode*, DOMNode*) {
    return nullptr;
}

DOMNode* DocumentAdapter::replaceChild(DOMNode*, DOMNode*) {
    return nullptr;
}

DOMNode* DocumentAdapter::removeChild(DOMNode*) {
    return nullptr;
}

DOMNode* DocumentAdapter::appendChild(DOMNode*) {
    return nullptr;
}

const XMLCh* DocumentAdapter::getNodeName() const {
    return adaptee->getNodeName().c_str();
}

const XMLCh* DocumentAdapter::getNodeValue() const {
    return adaptee->getNodeValue().c_str();
}

DOMNode::NodeType DocumentAdapter::getNodeType() const {
    switch (adaptee->getNodeType()) {
        case dom::Node::ATTRIBUTE_NODE:
            return DOMNode::ATTRIBUTE_NODE;
        case dom::Node::DOCUMENT_NODE:
            return DOMNode::DOCUMENT_NODE;
        case dom::Node::ELEMENT_NODE:
            return DOMNode::ELEMENT_NODE;
        case dom::Node::TEXT_NODE:
            return DOMNode::TEXT_NODE;
        default:
            return (DOMNode::NodeType)(0);
    }
}

DOMNodeList* DocumentAdapter::getChildNodes() const {
    return nullptr;
}

DOMDocument* DocumentAdapter::getOwnerDocument() const {
    return nullptr;
}

bool DocumentAdapter::hasChildNodes() const {
    return adaptee->hasChildNodes();
}

void DocumentAdapter::setNodeValue(const XMLCh* nodeValue) {
    adaptee->setNodeValue(nodeValue);
}

DOMNamedNodeMap* DocumentAdapter::getAttributes() const {
    return nullptr;
}

DOMNode* DocumentAdapter::cloneNode(bool) const {
    return nullptr;
}

void DocumentAdapter::normalize() {}

bool DocumentAdapter::isSupported(const XMLCh*, const XMLCh*) const {
    return false;
}

const XMLCh* DocumentAdapter::getNamespaceURI() const {
    return nullptr;
}

const XMLCh* DocumentAdapter::getPrefix() const {
    return nullptr;
}

const XMLCh* DocumentAdapter::getLocalName() const {
    return nullptr;
}

void DocumentAdapter::setPrefix(const XMLCh*) {}

bool DocumentAdapter::hasAttributes() const {
    return false;
}

bool DocumentAdapter::isSameNode(const DOMNode*) const {
    return false;
}

bool DocumentAdapter::isEqualNode(const DOMNode*) const {
    return false;
}

void* DocumentAdapter::setUserData(const XMLCh*, void*, DOMUserDataHandler*) {
    return nullptr;
}

void* DocumentAdapter::getUserData(const XMLCh*) const {
    return nullptr;
}

const XMLCh* DocumentAdapter::getBaseURI() const {
    return nullptr;
}

short DocumentAdapter::compareDocumentPosition(const DOMNode*) const {
    return 0;
}

const XMLCh* DocumentAdapter::getTextContent() const {
    return nullptr;
}

void DocumentAdapter::setTextContent(const XMLCh*) {}

const XMLCh* DocumentAdapter::lookupPrefix(const XMLCh*) const {
    return nullptr;
}

bool DocumentAdapter::isDefaultNamespace(const XMLCh*) const {
    return false;
}

const XMLCh* DocumentAdapter::lookupNamespaceURI(const XMLCh*) const {
    return nullptr;
}

void* DocumentAdapter::getFeature(const XMLCh*, const XMLCh*) const {
    return nullptr;
}

void DocumentAdapter::release() {}

DOMDocumentFragment* DocumentAdapter::createDocumentFragment() {
    return nullptr;
}

DOMComment* DocumentAdapter::createComment(const XMLCh*) {
    return nullptr;
}

DOMCDATASection* DocumentAdapter::createCDATASection(const XMLCh*) {
    return nullptr;
}

DOMProcessingInstruction*
DocumentAdapter::createProcessingInstruction(const XMLCh*, const XMLCh*) {
    return nullptr;
}

DOMEntityReference* DocumentAdapter::createEntityReference(const XMLCh*) {
    return nullptr;
}

DOMDocumentType* DocumentAdapter::getDoctype() const {
    return nullptr;
}

DOMImplementation* DocumentAdapter::getImplementation() const {
    return nullptr;
}

DOMNodeList* DocumentAdapter::getElementsByTagName(const XMLCh*) const {
    return nullptr;
}

DOMNode* DocumentAdapter::importNode(const DOMNode*, bool) {
    return nullptr;
}

DOMElement* DocumentAdapter::createElementNS(const XMLCh*, const XMLCh*) {
    return nullptr;
}

DOMAttr* DocumentAdapter::createAttributeNS(const XMLCh*, const XMLCh*) {
    return nullptr;
}

DOMNodeList* DocumentAdapter::getElementsByTagNameNS(const XMLCh*,
                                                     const XMLCh*) const {
    return nullptr;
}

DOMElement* DocumentAdapter::getElementById(const XMLCh*) const {
    return nullptr;
}

const XMLCh* DocumentAdapter::getInputEncoding() const {
    return nullptr;
}

const XMLCh* DocumentAdapter::getXmlEncoding() const {
    return nullptr;
}

bool DocumentAdapter::getXmlStandalone() const {
    return false;
}

void DocumentAdapter::setXmlStandalone(bool) {}

const XMLCh* DocumentAdapter::getXmlVersion() const {
    return nullptr;
}

void DocumentAdapter::setXmlVersion(const XMLCh*) {}

const XMLCh* DocumentAdapter::getDocumentURI() const {
    return nullptr;
}

void DocumentAdapter::setDocumentURI(const XMLCh*) {}

bool DocumentAdapter::getStrictErrorChecking() const {
    return false;
}

void DocumentAdapter::setStrictErrorChecking(bool) {}

DOMNode* DocumentAdapter::renameNode(DOMNode*, const XMLCh*, const XMLCh*) {
    return nullptr;
}

DOMNode* DocumentAdapter::adoptNode(DOMNode*) {
    return nullptr;
}

void DocumentAdapter::normalizeDocument() {}

DOMConfiguration* DocumentAdapter::getDOMConfig() const {
    return nullptr;
}

DOMEntity* DocumentAdapter::createEntity(const XMLCh*) {
    return nullptr;
}

DOMDocumentType* DocumentAdapter::createDocumentType(const XMLCh*) {
    return nullptr;
}

DOMNotation* DocumentAdapter::createNotation(const XMLCh*) {
    return nullptr;
}

DOMElement* DocumentAdapter::createElementNS(const XMLCh*, const XMLCh*,
                                             const XMLFileLoc,
                                             const XMLFileLoc) {
    return nullptr;
}
