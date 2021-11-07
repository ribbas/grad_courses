#include "Test.hpp"

void testSerializer(int argc, char** argv) {
    if (argc < 4) {
        printUsage();
        exit(0);
    }

    //
    // Create tree of this document:
    // <? xml version="1.0" encoding="UTF-8"?>
    // <document>
    //   <element attribute="attribute value"/>
    //   <element/>
    //   <element attribute="attribute value" attribute2="attribute2 value">
    //     Element Value
    //   </element>
    //   <element>
    //   </element>
    // </document>
    //
    dom::Document* document = new Document_Impl;
    dom::Element* root = document->createElement("document");
    document->appendChild(root);

    dom::Element* child = document->createElement("element");
    dom::Attr* attr = document->createAttribute("attribute");
    attr->setValue("attribute value");
    child->setAttributeNode(attr);
    root->appendChild(child);

    child = document->createElement("element");
    root->appendChild(child);

    child = document->createElement("element");
    child->setAttribute("attribute", "attribute value");
    child->setAttribute("attribute2", "attribute2 value");
    dom::Text* text = document->createTextNode("Element Value");
    child->appendChild(text);
    root->appendChild(child);

    child = document->createElement("element");
    root->appendChild(child);

    //
    // Serialize
    //
    std::fstream* file = nullptr;
    XMLSerializer xmlSerializer(
        file = new std::fstream(argv[2], std::ios_base::out));
    xmlSerializer.serializePretty(document);
    delete file;

    XMLSerializer xmlSerializer2(
        file = new std::fstream(argv[3], std::ios_base::out));
    xmlSerializer2.serializeMinimal(document);

    delete document;

    delete file;

    // delete Document and tree.
}
