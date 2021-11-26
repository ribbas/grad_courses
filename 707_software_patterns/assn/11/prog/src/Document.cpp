#include "Document.hpp"
#include "Attr.hpp"
#include "Element.hpp"
#include "NodeList.hpp"
#include "Text.hpp"
#include "XMLValidator.hpp"

Document_Impl::Document_Impl()
    : Node_Impl("", dom::Node::DOCUMENT_NODE, this) {}

Document_Impl::~Document_Impl() {
    destroyChildren(this);
}

void Document_Impl::destroyChildren(dom::Node* node) {

    if (node->hasChildNodes()) {

        for (dom::Node* i : *node->getChildNodes()) {

            if (i->hasChildNodes()) {
                destroyChildren(i);
            }
            delete i;
        }
    }
}

dom::Element* Document_Impl::createElement(const std::string& tagName) {
    return new Element_Impl(tagName, this);
}

dom::Text* Document_Impl::createTextNode(const std::string& data) {
    return new Text_Impl(data, this);
}

dom::Attr* Document_Impl::createAttribute(const std::string& name) {
    return new Attr_Impl(name, this);
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

dom::Iterator* Document_Impl::createIterator() {
    return new DocumentIterator(this);
}

void Document_Impl::serialize(std::fstream* writer,
                              WhitespaceStrategy* whitespace) {
    *writer << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
    whitespace->newLine(writer);
    getDocumentElement()->serialize(writer, whitespace);
}

dom::Node* Document_Impl::cloneNode() {
    return nullptr; // This implementation doesn't have the ability to reparent
                    // a cloned tree into a new document. Therefore it can't
                    // usefully support cloning of Document.
}
