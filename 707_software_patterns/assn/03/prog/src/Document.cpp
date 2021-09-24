#include "Document.hpp"
#include "Attr.hpp"
#include "Element.hpp"
#include "NodeList.hpp"
#include "Text.hpp"

Document_Impl::Document_Impl(void) : Node_Impl("", dom::Node::DOCUMENT_NODE) {
    Node_Impl::document = this;
}

Document_Impl::~Document_Impl() {}

// dom::Element* Document_Impl::createElement(const std::string& tagName) {
//     return new Element_Impl(tagName, this);
// }

dom::Element* Document_Impl::createElement(const std::string& tagName) {
    return dynamic_cast<dom::Element*>(
        documentNodeFactory->createDocumentNode(this, 0, tagName));
}

dom::Text* Document_Impl::createTextNode(const std::string& data) {
    return dynamic_cast<dom::Text*>(
        documentNodeFactory->createDocumentNode(this, 1, data));
}

dom::Attr* Document_Impl::createAttribute(const std::string& name) {
    return dynamic_cast<dom::Attr*>(
        documentNodeFactory->createDocumentNode(this, 2, name));
}

dom::Element* Document_Impl::getDocumentElement() {
    for (dom::NodeList::iterator i = getChildNodes()->begin();
         i != getChildNodes()->end(); i++) {
        if (dynamic_cast<dom::Element*>(*i.operator->()) != 0) {
            return dynamic_cast<dom::Element*>(*i.operator->());
        }
    }
    return 0;
}

dom::Node* DocumentNodeFactory::createDocumentNode(dom::Document* document,
                                                   int nodeType,
                                                   const std::string& value) {
    switch (nodeType) {
        case 0: {
            return new Element_Impl(value, document);
        }
        case 1: {
            return new Text_Impl(value, document);
        }
        case 2: {
            return new Attr_Impl(value, document);
        }

        default:
            return nullptr;
    }
}
