#include "XMLSerializer.hpp"

#include "Attr.hpp"
#include "Document.hpp"
#include "Element.hpp"
#include "Text.hpp"

XMLSerializer::XMLSerializer(std::fstream* _file)
    : file(_file), whitespace(new PrettyWhitespaceStrategy) {}

XMLSerializer::~XMLSerializer() {}

void XMLSerializer::serializePretty() {
    delete whitespace;
    whitespace = new PrettyWhitespaceStrategy;
}

void XMLSerializer::serializeMinimal() {
    delete whitespace;
    whitespace = new MinimalWhitespaceStrategy;
}

XMLSerializer::PrettyWhitespaceStrategy::PrettyWhitespaceStrategy()
    : indentationLevel(0) {}

void XMLSerializer::PrettyWhitespaceStrategy::prettyIndentation(
    std::fstream* writer) {
    for (int i = 0; i < indentationLevel; i++) {
        *writer << "\t";
    }
}

void XMLSerializer::PrettyWhitespaceStrategy::incrementIndentation() {
    indentationLevel++;
}

void XMLSerializer::PrettyWhitespaceStrategy::decrementIndentation() {
    indentationLevel--;
}

void XMLSerializer::PrettyWhitespaceStrategy::newLine(std::fstream* writer) {
    *writer << "\n";
}

void XMLSerializer::MinimalWhitespaceStrategy::prettyIndentation(
    std::fstream*) {}

void XMLSerializer::MinimalWhitespaceStrategy::incrementIndentation() {}

void XMLSerializer::MinimalWhitespaceStrategy::decrementIndentation() {}

void XMLSerializer::MinimalWhitespaceStrategy::newLine(std::fstream*) {}

void XMLSerializer::visitDocument(dom::Document* document) {
    *file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
    whitespace->newLine(file);
    document->getDocumentElement()->accept(this);
}

void XMLSerializer::visitElement(dom::Element* element) {
    whitespace->prettyIndentation(file);
    *file << "<" << element->getTagName();

    int attrCount = 0;

    for (dom::NamedNodeMap::iterator i = element->getAttributes()->begin();
         i != element->getAttributes()->end(); i++) {
        (*i)->accept(this);
        attrCount++;
    }

    if (attrCount > 0)
        *file << " ";

    if (element->getChildNodes()->size() == 0) {
        *file << "/>";
        whitespace->newLine(file);
    } else {
        *file << ">";
        whitespace->newLine(file);
        whitespace->incrementIndentation();

        for (dom::NodeList::iterator i = element->getChildNodes()->begin();
             i != element->getChildNodes()->end(); i++)
            if (dynamic_cast<dom::Element*>(*i) != 0 ||
                dynamic_cast<dom::Text*>(*i) != 0)
                (*i)->accept(this);

        whitespace->decrementIndentation();
        whitespace->prettyIndentation(file);
        *file << "</" << element->getTagName() + ">";
        whitespace->newLine(file);
    }
}

void XMLSerializer::visitAttr(dom::Attr* attr) {
    *file << " " << attr->getName() << "=\"" << attr->getValue() << "\"";
}

void XMLSerializer::visitText(dom::Text* text) {
    whitespace->prettyIndentation(file);
    *file << text->getData();
    whitespace->newLine(file);
}
