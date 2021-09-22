#include "Attr.hpp"

Attr_Impl::Attr_Impl(const std::string& tagName, dom::Document* document)
    : DocumentNode_Impl(tagName, dom::Node::ATTRIBUTE_NODE, document) {}

Attr_Impl::Attr_Impl(const std::string& tagName, const std::string& value,
                     dom::Document* document)
    : DocumentNode_Impl(tagName, dom::Node::ATTRIBUTE_NODE, document) {
    setNodeValue(value);
}

Attr_Impl::~Attr_Impl() {}

dom::Element* Attr_Impl::getOwnerElement(void) {
    return (dom::Element*)DocumentNode_Impl::getParentNode();
}
