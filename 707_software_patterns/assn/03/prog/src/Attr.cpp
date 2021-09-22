#include "Attr.hpp"

Attr_Impl::Attr_Impl(const std::string& tagName, dom::Document* document)
    : DocumentNode_Impl(tagName, dom::Node::ATTRIBUTE_NODE, document) {
    // DocumentNode_Impl::document = document;
}

Attr_Impl::Attr_Impl(const std::string& tagName, const std::string& value,
                     dom::Document* document)
    : DocumentNode_Impl(tagName, dom::Node::ATTRIBUTE_NODE, document) {
    // DocumentNode_Impl::document = document;
    setNodeValue(value);
}

Attr_Impl::~Attr_Impl() {}

// const std::string& Attr_Impl::getName(void) {
//     return getNodeName();
// }

// const std::string& Attr_Impl::getValue(void) {
//     return DocumentNode_Impl::getNodeValue();
// }

// void Attr_Impl::setValue(const std::string& value) {
//     DocumentNode_Impl::setNodeValue(value);
// }

dom::Element* Attr_Impl::getOwnerElement(void) {
    return (dom::Element*)DocumentNode_Impl::getParentNode();
}
