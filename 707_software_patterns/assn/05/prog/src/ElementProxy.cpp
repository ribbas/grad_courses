#include "ElementProxy.hpp"
#include <iostream>

ElementProxy::ElementProxy(const std::string& tagName, dom::Document* document)
    : realSubject(nullptr), tagName(tagName), document(document),
      realized(false), offset(0) {}

ElementProxy::~ElementProxy() {
    offset = 0;
    delete realSubject;
}

dom::Element* ElementProxy::getRealSubject() {
    return realSubject;
}

void ElementProxy::serialize(std::fstream* writer,
                             WhitespaceStrategy* whitespace) {
    realSubject->serialize(writer, whitespace);
}

const std::string& ElementProxy::getAttribute(const std::string& name) {
    return realSubject->getAttribute(name);
}

dom::Attr* ElementProxy::getAttributeNode(const std::string& name) {
    return realSubject->getAttributeNode(name);
}

dom::NodeList* ElementProxy::getElementsByTagName(const std::string& tagName) {
    return realSubject->getElementsByTagName(tagName);
}

bool ElementProxy::hasAttribute(const std::string& name) {
    return realSubject->hasAttribute(name);
}

void ElementProxy::removeAttribute(const std::string& name) {
    realSubject->removeAttribute(name);
}

dom::Attr* ElementProxy::removeAttributeNode(dom::Attr* oldAttr) {
    return realSubject->removeAttributeNode(oldAttr);
}

dom::NamedNodeMap* ElementProxy::getAttributes() {
    return realSubject->getAttributes();
}

bool ElementProxy::hasAttributes() {
    return realSubject->hasAttributes();
}

const std::string& ElementProxy::getNodeName() {
    return realSubject->getNodeName();
}

const std::string& ElementProxy::getNodeValue() {
    return realSubject->getNodeValue();
}

void ElementProxy::setNodeValue(const std::string& nodeValue) {
    realSubject->setNodeValue(nodeValue);
}

short ElementProxy::getNodeType() {
    return realSubject->getNodeType();
}

dom::Node* ElementProxy::getParentNode() {
    return realSubject->getParentNode();
}

dom::Node* ElementProxy::getPreviousSibling() {
    return realSubject->getPreviousSibling();
}

dom::Node* ElementProxy::getNextSibling() {
    return realSubject->getNextSibling();
}

dom::Node* ElementProxy::removeChild(Node* oldChild) {
    return realSubject->removeChild(oldChild);
}

dom::Node* ElementProxy::insertBefore(dom::Node* newChild,
                                      dom::Node* refChild) {
    return realSubject->insertBefore(newChild, refChild);
}

dom::Node* ElementProxy::replaceChild(dom::Node* newChild,
                                      dom::Node* refChild) {
    return realSubject->replaceChild(newChild, refChild);
}

const std::string& ElementProxy::getLocalName() {
    return realSubject->getLocalName();
}

void ElementProxy::realize() {
    if (!realized) {
        realSubject = new Element_Impl(tagName, document);
        realized = true;
    }
}

/* Methods that need the real object instantiated */
const std::string& ElementProxy::getTagName() {
    realize();
    return realSubject->getTagName();
}

void ElementProxy::setAttribute(const std::string& name,
                                const std::string& value) {
    realize();
    realSubject->setAttribute(name, value);
}

dom::Attr* ElementProxy::setAttributeNode(dom::Attr* newAttr) {
    realize();
    return realSubject->setAttributeNode(newAttr);
}

dom::Document* ElementProxy::getOwnerDocument() {
    realize();
    return realSubject->getOwnerDocument();
}

dom::Node* ElementProxy::appendChild(dom::Node* newChild) {
    realize();
    // director->loadRealElement(this);
    return realSubject->appendChild(newChild);
}

dom::NodeList* ElementProxy::getChildNodes() {

    realize();
    // director->loadRealElement(this);
    return realSubject->getChildNodes();
}

dom::Node* ElementProxy::getFirstChild() {

    realize();
    // director->loadRealElement(this);
    return realSubject->getFirstChild();
}

dom::Node* ElementProxy::getLastChild() {

    realize();
    // director->loadRealElement(this);
    return realSubject->getLastChild();
}

bool ElementProxy::hasChildNodes() {

    realize();
    // director->loadRealElement(this);
    return realSubject->hasChildNodes();
}
