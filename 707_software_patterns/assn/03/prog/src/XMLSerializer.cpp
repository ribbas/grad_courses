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