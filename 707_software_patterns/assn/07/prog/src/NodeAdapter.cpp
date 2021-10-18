#include "NodeAdapter.hpp"
#include "DocumentAdapter.hpp"

NodeAdapter::NodeAdapter(const std::string& name, short type,
                         dom::Document* document)
    : adaptee(new Node_Impl(name, type, document)) {}

NodeAdapter::NodeAdapter(dom::Node* _adaptee) : adaptee(_adaptee) {}

dom::Node* NodeAdapter::getAdaptee() {
    return adaptee;
}

const XERCES::XMLCh* NodeAdapter::getNodeName() const {
    return (XERCES::XMLCh*)adaptee->getNodeName().c_str();
}

const XERCES::XMLCh* NodeAdapter::getNodeValue() const {
    return (XERCES::XMLCh*)adaptee->getNodeValue().c_str();
}

XERCES::DOMNode::NodeType NodeAdapter::getNodeType() const {
    switch (adaptee->getNodeType()) {
        case dom::Node::ATTRIBUTE_NODE:
            return XERCES::DOMNode::ATTRIBUTE_NODE;
        case dom::Node::DOCUMENT_NODE:
            return XERCES::DOMNode::DOCUMENT_NODE;
        case dom::Node::ELEMENT_NODE:
            return XERCES::DOMNode::ELEMENT_NODE;
        case dom::Node::TEXT_NODE:
            return XERCES::DOMNode::TEXT_NODE;
    }
}

XERCES::DOMNode* NodeAdapter::getParentNode() const {
    return dynamic_cast<XERCES::DOMNode*>(
        new NodeAdapter(adaptee->getParentNode()));
}

XERCES::DOMNodeList* NodeAdapter::getChildNodes() const {
    return nullptr; // dynamic_cast<XERCES::DOMNodeList *>(new
                    // NodeList(adaptee->getChildNodes()));
}

XERCES::DOMNode* NodeAdapter::getFirstChild() const {
    return dynamic_cast<XERCES::DOMNode*>(
        new NodeAdapter(adaptee->getFirstChild()));
}

XERCES::DOMNode* NodeAdapter::getLastChild() const {
    return dynamic_cast<XERCES::DOMNode*>(
        new NodeAdapter(adaptee->getLastChild()));
}

XERCES::DOMNode* NodeAdapter::getPreviousSibling() const {
    return dynamic_cast<XERCES::DOMNode*>(
        new NodeAdapter(adaptee->getPreviousSibling()));
}

XERCES::DOMNode* NodeAdapter::getNextSibling() const {
    return dynamic_cast<XERCES::DOMNode*>(
        new NodeAdapter(adaptee->getNextSibling()));
}

XERCES::DOMDocument* NodeAdapter::getOwnerDocument() const {
    return dynamic_cast<XERCES::DOMDocument*>(
        new DocumentAdapter(adaptee->getOwnerDocument()));
}

XERCES::DOMNode* NodeAdapter::insertBefore(XERCES::DOMNode* newChild,
                                           XERCES::DOMNode* refChild) {
    return dynamic_cast<XERCES::DOMNode*>(new NodeAdapter(adaptee->insertBefore(
        dynamic_cast<NodeAdapter*>(newChild)->getAdaptee(),
        dynamic_cast<NodeAdapter*>(refChild)->getAdaptee())));
}

XERCES::DOMNode* NodeAdapter::replaceChild(XERCES::DOMNode* newChild,
                                           XERCES::DOMNode* oldChild) {
    return dynamic_cast<XERCES::DOMNode*>(new NodeAdapter(adaptee->replaceChild(
        dynamic_cast<NodeAdapter*>(newChild)->getAdaptee(),
        dynamic_cast<NodeAdapter*>(oldChild)->getAdaptee())));
}

XERCES::DOMNode* NodeAdapter::removeChild(XERCES::DOMNode* oldChild) {
    return dynamic_cast<XERCES::DOMNode*>(new NodeAdapter(adaptee->removeChild(
        dynamic_cast<NodeAdapter*>(oldChild)->getAdaptee())));
}

XERCES::DOMNode* NodeAdapter::appendChild(XERCES::DOMNode* newChild) {
    return dynamic_cast<XERCES::DOMNode*>(new NodeAdapter(adaptee->appendChild(
        dynamic_cast<NodeAdapter*>(newChild)->getAdaptee())));
}

bool NodeAdapter::hasChildNodes() const {
    return adaptee->hasChildNodes();
}

void NodeAdapter::setNodeValue(const XERCES::XMLCh* nodeValue) {
    adaptee->setNodeValue((char*)nodeValue);
}

XERCES::DOMNamedNodeMap* NodeAdapter::getAttributes() const {
    return nullptr;
}
XERCES::DOMNode* NodeAdapter::cloneNode(bool) const {
    return nullptr;
}

void NodeAdapter::normalize() {}

bool NodeAdapter::isSupported(const XERCES::XMLCh*,
                              const XERCES::XMLCh*) const {
    return false;
}
const XERCES::XMLCh* NodeAdapter::getNamespaceURI() const {
    return nullptr;
}
const XERCES::XMLCh* NodeAdapter::getPrefix() const {
    return nullptr;
}
const XERCES::XMLCh* NodeAdapter::getLocalName() const {
    return nullptr;
}
void NodeAdapter::setPrefix(const XERCES::XMLCh*) {}
bool NodeAdapter::hasAttributes() const {
    return false;
}
bool NodeAdapter::isSameNode(const XERCES::DOMNode*) const {
    return false;
}
bool NodeAdapter::isEqualNode(const XERCES::DOMNode*) const {
    return false;
}
void* NodeAdapter::setUserData(const XERCES::XMLCh*, void*,
                               XERCES::DOMUserDataHandler*) {
    return nullptr;
}
void* NodeAdapter::getUserData(const XERCES::XMLCh*) const {
    return nullptr;
}
const XERCES::XMLCh* NodeAdapter::getBaseURI() const {
    return nullptr;
}
short NodeAdapter::compareDocumentPosition(const XERCES::DOMNode*) const {
    return 0;
}
const XERCES::XMLCh* NodeAdapter::getTextContent() const {
    return nullptr;
}
void NodeAdapter::setTextContent(const XERCES::XMLCh*) {}
const XERCES::XMLCh* NodeAdapter::lookupPrefix(const XERCES::XMLCh*) const {
    return nullptr;
}
bool NodeAdapter::isDefaultNamespace(const XERCES::XMLCh*) const {
    return false;
}
const XERCES::XMLCh*
NodeAdapter::lookupNamespaceURI(const XERCES::XMLCh*) const {
    return nullptr;
}
void* NodeAdapter::getFeature(const XERCES::XMLCh*,
                              const XERCES::XMLCh*) const {
    return nullptr;
}
void NodeAdapter::release() {}
