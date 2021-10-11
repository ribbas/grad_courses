#include "ElementProxy.hpp"

ElementProxy::ElementProxy(const std::string& tagName, dom::Document* document)
    : realSubject(nullptr), tagName(tagName), document(document),
      realized(false), streamPos(0) {}

ElementProxy::~ElementProxy() {
    streamPos = 0;
    delete realSubject;
}

dom::Element* ElementProxy::getRealSubject() {
    return realSubject;
}

void ElementProxy::setStreamPos(int streamPos_) {
    streamPos = streamPos_;
}

void ElementProxy::setDirector(XMLDirector* director_) {
    director = director_;
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
    // director->resumeParse(this);
    return realSubject->appendChild(newChild);
}

dom::NodeList* ElementProxy::getChildNodes() {

    realize();
    // director->resumeParse(this);
    return realSubject->getChildNodes();
}

dom::Node* ElementProxy::getFirstChild() {

    realize();
    // director->resumeParse(this);
    return realSubject->getFirstChild();
}

dom::Node* ElementProxy::getLastChild() {

    realize();
    // director->resumeParse(this);
    return realSubject->getLastChild();
}

bool ElementProxy::hasChildNodes() {

    realize();
    // director->resumeParse(this);
    return realSubject->hasChildNodes();
}
