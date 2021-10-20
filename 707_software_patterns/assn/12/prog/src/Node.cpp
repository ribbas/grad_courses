#include "Node.hpp"

Node_Impl::Node_Impl(const std::string& name, short type,
                     dom::Document* document)
    : name(name), nodeType(type), parent(nullptr), document(document) {}

Node_Impl::~Node_Impl() {}

const std::string& Node_Impl::getNodeName() {
    return name;
}

const std::string& Node_Impl::getNodeValue() {
    return value;
}

void Node_Impl::setNodeValue(const std::string& nodeValue) {
    value = nodeValue;
}

short Node_Impl::getNodeType() {
    return nodeType;
}

dom::Node* Node_Impl::getParentNode() {
    return parent;
}

dom::NodeList* Node_Impl::getChildNodes() {
    return &nodes;
}

dom::Node* Node_Impl::getFirstChild() {
    return *nodes.begin();
}

dom::Node* Node_Impl::getLastChild() {
    return *(--nodes.end());
}

dom::Node* Node_Impl::getPreviousSibling() {
    return getSibling(-1);
}

dom::Node* Node_Impl::getNextSibling() {
    return getSibling(1);
}

dom::Document* Node_Impl::getOwnerDocument() {
    return document;
}

dom::Node* Node_Impl::insertBefore(dom::Node* newChild, dom::Node* refChild) {
    if (newChild->getOwnerDocument() != getOwnerDocument()) {
        throw dom::DOMException(dom::DOMException::WRONG_DOCUMENT_ERR,
                                "New Child is not a part of this document.");
    }

    if (newChild->getParentNode() != 0) {
        newChild->getParentNode()->removeChild(newChild);
    }

    if (refChild == 0) {
        nodes.push_back(newChild);
        (dynamic_cast<Node_Impl*>(newChild))->setParent(this);
        return newChild;
    }

    dom::NodeList::iterator index = nodes.find(refChild);

    if (index == nodes.end()) {
        throw dom::DOMException(dom::DOMException::NOT_FOUND_ERR,
                                "Reference Child is not a child of this node.");
    }

    nodes.insert(++index, newChild);
    (dynamic_cast<Node_Impl*>(newChild))->setParent(this);

    return newChild;
}

dom::Node* Node_Impl::replaceChild(dom::Node* newChild, dom::Node* oldChild) {
    if (newChild->getOwnerDocument() != getOwnerDocument()) {
        throw dom::DOMException(dom::DOMException::WRONG_DOCUMENT_ERR,
                                "New Child is not a part of this document.");
    }

    if (newChild->getParentNode() != 0) {
        newChild->getParentNode()->removeChild(newChild);
    }

    dom::NodeList::iterator index = nodes.find(oldChild);

    if (index == nodes.end()) {
        throw dom::DOMException(dom::DOMException::NOT_FOUND_ERR,
                                "Old Child is not a child of this node.");
    }

    nodes.insert(index, newChild);
    (dynamic_cast<Node_Impl*>(newChild))->setParent(this);
    (dynamic_cast<Node_Impl*>(*index))->setParent(0);
    nodes.erase(index);

    return oldChild;
}

dom::Node* Node_Impl::removeChild(dom::Node* oldChild) {
    dom::NodeList::iterator index = nodes.find(oldChild);

    if (index == nodes.end()) {
        throw dom::DOMException(dom::DOMException::NOT_FOUND_ERR,
                                "Old Child is not a child of this node.");
    }

    (dynamic_cast<Node_Impl*>(*index))->setParent(0);
    nodes.erase(index);

    return oldChild;
}

dom::Node* Node_Impl::appendChild(dom::Node* newChild) {
    if (newChild->getOwnerDocument() != getOwnerDocument()) {
        throw dom::DOMException(dom::DOMException::WRONG_DOCUMENT_ERR,
                                "New Child is not a part of this document.");
    }

    if (newChild->getParentNode() != 0) {
        newChild->getParentNode()->removeChild(newChild);
    }

    nodes.push_back(newChild);
    (dynamic_cast<Node_Impl*>(newChild))->setParent(this);

    return newChild;
}

bool Node_Impl::hasChildNodes() {
    return nodes.size() > 0;
}

const std::string& Node_Impl::getLocalName() {
    return name;
}

void Node_Impl::setParent(dom::Node* parent) {
    this->parent = parent;
}

dom::Node* Node_Impl::getSibling(int direction) {
    if (parent == 0) {
        return 0;
    }

    dom::NodeList::iterator i = parent->getChildNodes()->find(this);

    if (direction < 0) {
        if (i == parent->getChildNodes()->begin()) {
            return 0;
        } else {
            return *(--i);
        }
    } else {
        i++;

        if (i == parent->getChildNodes()->end()) {
            return 0;
        } else {
            return *i;
        }
    }
}