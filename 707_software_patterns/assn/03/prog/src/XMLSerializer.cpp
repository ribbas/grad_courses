#include "XMLSerializer.hpp"

#include "Attr.hpp"
#include "Document.hpp"
#include "Element.hpp"
#include "Text.hpp"

void XMLSerializer::serializePretty(dom::Node* node) {
    WhitespaceStrategy* ws = new PrettyWhitespaceStrategy;
    node->serialize(file, ws);
    delete ws;
}

void XMLSerializer::serializeMinimal(dom::Node* node) {
    WhitespaceStrategy* ws = new MinimalWhitespaceStrategy;
    node->serialize(file, ws);
    delete ws;
}

XMLSerializer::PrettyWhitespaceStrategy::PrettyWhitespaceStrategy()
    : indentationLevel(0) {}

void XMLSerializer::PrettyWhitespaceStrategy::prettyIndentation(
    std::fstream* wwriter) {
    for (int i = 0; i < indentationLevel; i++)
        *wwriter << "\t";
}

void XMLSerializer::PrettyWhitespaceStrategy::incrementIndentation() {
    indentationLevel++;
}
void XMLSerializer::PrettyWhitespaceStrategy::decrementIndentation() {
    indentationLevel--;
}
void XMLSerializer::PrettyWhitespaceStrategy::newLine(std::fstream* wwriter) {
    *wwriter << "\n";
}

void XMLSerializer::MinimalWhitespaceStrategy::prettyIndentation(
    std::fstream*) {}
void XMLSerializer::MinimalWhitespaceStrategy::incrementIndentation() {}
void XMLSerializer::MinimalWhitespaceStrategy::decrementIndentation() {}
void XMLSerializer::MinimalWhitespaceStrategy::newLine(std::fstream*) {}