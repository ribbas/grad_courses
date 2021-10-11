#include "Document.hpp"
#include "Attr.hpp"
#include "Element.hpp"
#include "ElementProxy.hpp"
#include "NodeList.hpp"
#include "Text.hpp"
#include "XMLValidator.hpp"

Document_Impl::Document_Impl() : Node_Impl("", dom::Node::DOCUMENT_NODE) {
    Node_Impl::document = this;
}

Document_Impl::~Document_Impl() {}

void Document_Impl::serialize(std::fstream* writer,
                              WhitespaceStrategy* whitespace) {
    *writer << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
    whitespace->newLine(writer);
    getDocumentElement()->serialize(writer, whitespace);
}

dom::Element* Document_Impl::createElement(const std::string& tagName,
                                           int offset, XMLDirector* director) {
    dom::Element* element = new ElementProxy(tagName, this);
    element->setOffset(offset);
    element->setDirector(director);
    return element;
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
