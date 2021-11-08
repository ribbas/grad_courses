#include "Test.hpp"

void testIterator(int argc, char**) {

    if (argc < 3) {
        printUsage();
        exit(0);
    }

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
    // Create an iterator from the document object
    //
    dom::Iterator* it = document->createIterator();
    dom::Node* currentNode;
    for (it->first(); !it->isDone(); it->next()) {

        currentNode = it->currentItem();

        if (dynamic_cast<dom::Document*>(currentNode) != 0) {
            std::cout << "Document: " << currentNode << std::endl;
        } else if (dynamic_cast<dom::Element*>(currentNode) != 0) {
            std::cout << "Element: " << currentNode << std::endl;
        } else if (dynamic_cast<dom::Attr*>(currentNode) != 0) {
            std::cout << "Attr: " << currentNode << std::endl;
        } else if (dynamic_cast<dom::Text*>(currentNode) != 0) {
            std::cout << "Text: " << currentNode << std::endl;
        }
    }

    delete document;
    delete it;
}