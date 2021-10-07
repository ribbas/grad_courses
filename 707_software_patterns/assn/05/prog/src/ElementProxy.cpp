#include "ElementProxy.hpp"
#include <iostream>

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
const std::string& ElementProxy::getTagName() {
    if (!realized) {
        std::cout << "realizing\n";
        realize();
    }
    return realSubject->getTagName();
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
void ElementProxy::setAttribute(const std::string& name,
                                const std::string& value) {
    if (!realized) {
        std::cout << "realizing\n";
        realize();
    }
    realSubject->setAttribute(name, value);
}
dom::Attr* ElementProxy::setAttributeNode(dom::Attr* newAttr) {
    if (!realized) {
        std::cout << "realizing\n";
        realize();
    }
    return realSubject->setAttributeNode(newAttr);
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
dom::Document* ElementProxy::getOwnerDocument() {
    if (!realized) {
        std::cout << "realizing\n";
        realize();
    }
    return realSubject->getOwnerDocument();
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
dom::Node* ElementProxy::appendChild(dom::Node* newChild) {
    if (!realized) {
        std::cout << "realizing\n";
        realize();
    }
    return realSubject->appendChild(newChild);
}

const std::string& ElementProxy::getLocalName() {
    return realSubject->getLocalName();
}

void ElementProxy::realize(void) {
    // Realize by parsing child nodes.
    realSubject = new Element_Impl(tagName, document);
    realized = true;
}

dom::NodeList* ElementProxy::getChildNodes(void) {
    if (!realized) {
        realize();
    }

    return realSubject->getChildNodes();
}

dom::Node* ElementProxy::getFirstChild(void) {
    if (!realized) {
        realize();
    }

    return realSubject->getFirstChild();
}

dom::Node* ElementProxy::getLastChild(void) {
    if (!realized) {
        realize();
    }

    return realSubject->getLastChild();
}

bool ElementProxy::hasChildNodes(void) {
    if (!realized) {
        realize();
    }

    return realSubject->hasChildNodes();
}
