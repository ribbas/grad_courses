#include "Attr.hpp"

Attr_Impl::Attr_Impl(const std::string& tagName, dom::Document* document)
    : Node_Impl(tagName, dom::Node::ATTRIBUTE_NODE, document) {}

Attr_Impl::Attr_Impl(const std::string& tagName, const std::string& value,
                     dom::Document* document)
    : Node_Impl(tagName, dom::Node::ATTRIBUTE_NODE, document) {
    setValue(value);
}

Attr_Impl::~Attr_Impl() {}

const std::string& Attr_Impl::getName() {
    return Node_Impl::getNodeName();
}

const std::string& Attr_Impl::getValue() {
    return Node_Impl::getNodeValue();
}

void Attr_Impl::setValue(const std::string& value) {
    Node_Impl::setNodeValue(value);
}

dom::Element* Attr_Impl::getOwnerElement() {
    return (dom::Element*)Node_Impl::getParentNode();
}

dom::Node* Attr_Impl::insertBefore(dom::Node*, dom::Node*) {
    throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR,
                            "Attr nodes do not support this method.");
}

dom::Node* Attr_Impl::replaceChild(dom::Node*, dom::Node*) {
    throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR,
                            "Attr nodes do not support this method.");
}

dom::Node* Attr_Impl::removeChild(dom::Node*) {
    throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR,
                            "Attr nodes do not support this method.");
}

dom::Node* Attr_Impl::appendChild(dom::Node*) {
    throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR,
                            "Attr nodes do not support this method.");
}

void Attr_Impl::accept(XMLVisitor* visitor) {
    visitor->visitAttr(this);
}
