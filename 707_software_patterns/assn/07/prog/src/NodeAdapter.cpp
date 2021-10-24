#include "NodeAdapter.hpp"
#include "DocumentAdapter.hpp"

using namespace XERCES;

NodeAdapter::NodeAdapter(const std::string& name, short type,
                         dom::Document* document)
    : adaptee(new Node_Impl(name, type, document)) {}

NodeAdapter::NodeAdapter(dom::Node* _adaptee) : adaptee(_adaptee) {}

NodeAdapter::~NodeAdapter() {
    if (adaptee) {
        delete adaptee;
    }
}

const XMLCh* NodeAdapter::getNodeName() const {
    return adaptee->getNodeName().c_str();
}

const XMLCh* NodeAdapter::getNodeValue() const {
    return adaptee->getNodeValue().c_str();
}

DOMNode::NodeType NodeAdapter::getNodeType() const {
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

DOMNode* NodeAdapter::getParentNode() const {
    return dynamic_cast<DOMNode*>(
        new NodeAdapter(adaptee->getParentNode()));
}

DOMNodeList* NodeAdapter::getChildNodes() const {
    // once the DOMNodeList class is implemented, the following can instead be
    // returned:
    // dynamic_cast<DOMNodeList*>(new
    // NodeList(adaptee->getChildNodes()));
    return nullptr;
}

DOMNode* NodeAdapter::getFirstChild() const {
    return dynamic_cast<DOMNode*>(
        new NodeAdapter(adaptee->getFirstChild()));
}

DOMNode* NodeAdapter::getLastChild() const {
    return dynamic_cast<DOMNode*>(
        new NodeAdapter(adaptee->getLastChild()));
}

DOMNode* NodeAdapter::getPreviousSibling() const {
    return dynamic_cast<DOMNode*>(
        new NodeAdapter(adaptee->getPreviousSibling()));
}

DOMNode* NodeAdapter::getNextSibling() const {
    return dynamic_cast<DOMNode*>(
        new NodeAdapter(adaptee->getNextSibling()));
}

DOMDocument* NodeAdapter::getOwnerDocument() const {
    return dynamic_cast<DOMDocument*>(
        new DocumentAdapter(adaptee->getOwnerDocument()));
}

DOMNode* NodeAdapter::insertBefore(DOMNode* newChild,
                                           DOMNode* refChild) {
    return new NodeAdapter(
        adaptee->insertBefore(dynamic_cast<NodeAdapter*>(newChild)->adaptee,
                              dynamic_cast<NodeAdapter*>(refChild)->adaptee));
}

DOMNode* NodeAdapter::replaceChild(DOMNode* newChild,
                                           DOMNode* oldChild) {
    return new NodeAdapter(
        adaptee->replaceChild(dynamic_cast<NodeAdapter*>(newChild)->adaptee,
                              dynamic_cast<NodeAdapter*>(oldChild)->adaptee));
}

DOMNode* NodeAdapter::removeChild(DOMNode* oldChild) {
    return new NodeAdapter(
        adaptee->removeChild(dynamic_cast<NodeAdapter*>(oldChild)->adaptee));
}

DOMNode* NodeAdapter::appendChild(DOMNode* newChild) {
    return new NodeAdapter(
        adaptee->appendChild(dynamic_cast<NodeAdapter*>(newChild)->adaptee));
}

bool NodeAdapter::hasChildNodes() const {
    return adaptee->hasChildNodes();
}

void NodeAdapter::setNodeValue(const XMLCh* nodeValue) {
    adaptee->setNodeValue((char*)nodeValue);
}

DOMNamedNodeMap* NodeAdapter::getAttributes() const {
    return nullptr;
}

DOMNode* NodeAdapter::cloneNode(bool) const {
    return nullptr;
}

void NodeAdapter::normalize() {}

bool NodeAdapter::isSupported(const XMLCh*,
                              const XMLCh*) const {
    return false;
}

const XMLCh* NodeAdapter::getNamespaceURI() const {
    return nullptr;
}

const XMLCh* NodeAdapter::getPrefix() const {
    return nullptr;
}

const XMLCh* NodeAdapter::getLocalName() const {
    return nullptr;
}

void NodeAdapter::setPrefix(const XMLCh*) {}

bool NodeAdapter::hasAttributes() const {
    return false;
}

bool NodeAdapter::isSameNode(const DOMNode*) const {
    return false;
}

bool NodeAdapter::isEqualNode(const DOMNode*) const {
    return false;
}
void* NodeAdapter::setUserData(const XMLCh*, void*,
                               DOMUserDataHandler*) {
    return nullptr;
}

void* NodeAdapter::getUserData(const XMLCh*) const {
    return nullptr;
}

const XMLCh* NodeAdapter::getBaseURI() const {
    return nullptr;
}

short NodeAdapter::compareDocumentPosition(const DOMNode*) const {
    return 0;
}

const XMLCh* NodeAdapter::getTextContent() const {
    return nullptr;
}

void NodeAdapter::setTextContent(const XMLCh*) {}

const XMLCh* NodeAdapter::lookupPrefix(const XMLCh*) const {
    return nullptr;
}

bool NodeAdapter::isDefaultNamespace(const XMLCh*) const {
    return false;
}

const XMLCh*
NodeAdapter::lookupNamespaceURI(const XMLCh*) const {
    return nullptr;
}

void* NodeAdapter::getFeature(const XMLCh*,
                              const XMLCh*) const {
    return nullptr;
}

void NodeAdapter::release() {}
