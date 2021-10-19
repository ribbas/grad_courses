#include "Attr.hpp"
#include "DOMDocument.hpp"
#include "DOMNode.hpp"
#include "Document.hpp"
#include "DocumentAdapter.hpp"
#include "Element.hpp"
#include "NodeAdapter.hpp"
#include "Text.hpp"
#include "XMLBuilder.hpp"
#include "XMLDirector.hpp"
#include "XMLSerializer.hpp"
#include "XMLTokenizer.hpp"
#include "XMLValidator.hpp"

#include <iostream>
#include <stdio.h>

void testTokenizer(int, char**);
void testSerializer(int, char**);
void testValidator(int, char**);
void testBuilder(int, char**);
void testIterator(int, char**);
void testAdapter(int, char**);

void printUsage() {
    std::cout << "Usage:\n"
              << "\tTest b [file1] [file2]\n"
              << "\tTest i [file] ...\n"
              << "\tTest t [file] ...\n"
              << "\tTest s [file1] [file2]\n"
              << "\tTest v [file]\n";
}

int main(int argc, char** argv) {

    if (argc < 2) {
        printUsage();
        exit(0);
    }

    switch (argv[1][0]) {
        case 'A':
        case 'a':
            testAdapter(argc, argv);
            break;
        case 'B':
        case 'b':
            testBuilder(argc, argv);
            break;
        case 'I':
        case 'i':
            testIterator(argc, argv);
            break;
        case 'T':
        case 't':
            testTokenizer(argc, argv);
            break;
        case 'S':
        case 's':
            testSerializer(argc, argv);
            break;
        case 'V':
        case 'v':
            testValidator(argc, argv);
            break;
    }
}

void testAdapter(int, char**) {}

void testBuilder(int argc, char** argv) {

    if (argc < 4) {
        printUsage();
        exit(0);
    }

    XMLBuilder* builder = new XMLBuilder();
    XMLDirector director(builder, argv[2]);
    director.construct();
    dom::Document* builtDocument = director.getResult();

    std::cout << "DOM Tree successfully built\n";

    //
    // Serialize
    //
    std::fstream* file = 0;
    XMLSerializer xmlSerializer(
        file = new std::fstream(argv[3], std::ios_base::out));
    xmlSerializer.serializePretty(builtDocument);

    delete builtDocument;
    delete builder;
    delete file;
}

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
            std::cout << "Document: " << currentNode << '\n';
        } else if (dynamic_cast<dom::Element*>(currentNode) != 0) {
            std::cout << "Element: " << currentNode << '\n';
        } else if (dynamic_cast<dom::Attr*>(currentNode) != 0) {
            std::cout << "Attr: " << currentNode << '\n';
        } else if (dynamic_cast<dom::Text*>(currentNode) != 0) {
            std::cout << "Text: " << currentNode << '\n';
        }
    }

    delete document;
    delete it;
}

void testTokenizer(int argc, char** argv) {

    dom::Document* document = new Document_Impl;

    dom::Element* element = document->createElement("NewElement");
    dom::Text* text = document->createTextNode("Text Data");
    dom::Attr* attr = document->createAttribute("NewAttribute");

    std::cout << "Element Tag = '" << element->getTagName() << "'\n";
    std::cout << "Text Data = '" << text->getValue() << "'\n";
    std::cout << "Attr Name = '" << attr->getName() << "'\n";

    element->setAttributeNode(attr);
    std::cout << "Element attribute '" << element->getTagName() << "'='"
              << element->getAttribute("NewAttribute") << "'\n";

    delete element;
    delete text;
    delete document;

    for (int i = 2; i < argc; i++) {
        XMLTokenizer tokenizer(argv[i]);

        XMLTokenizer::XMLToken* token = 0;

        std::cout << "File:  '" << argv[i] << "'\n";

        do {
            delete token;
            token = tokenizer.getNextToken();

            std::cout << "\tLine " << tokenizer.getLineNumber() << ":  "
                      << token->toString() << " = '"
                      << (token->getToken().size() == 0 ? ""
                                                        : token->getToken())
                      << "'\n";

        } while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN);

        delete token;
    }
}

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
    std::fstream* file = 0;
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

void testValidator(int argc, char** argv) {
    if (argc < 3) {
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
    // Schema for this document:
    // document contains:  element
    // element contains:  element
    // element contains attributes:  attribute, attribute2
    //
    XMLValidator xmlValidator;
    ValidChildren* schemaElement = xmlValidator.addSchemaElement("");
    schemaElement->addValidChild("document", false);
    schemaElement = xmlValidator.addSchemaElement("document");
    schemaElement->addValidChild("element", false);
    schemaElement = xmlValidator.addSchemaElement("element");
    schemaElement->addValidChild("element", false);
    schemaElement->addValidChild("attribute", true);
    schemaElement->addValidChild("attribute2", true);
    schemaElement->setCanHaveText(true);

    dom::Document* document = new Document_Impl;
    dom::Element* root = 0;
    dom::Element* child = 0;
    dom::Attr* attr = 0;

    if (xmlValidator.canRootElement("document")) {
        root = document->createElement("document");
        document->appendChild(root);
    } else {
        std::cout << "Attempted invalid schema operation.\n";
        exit(0);
    }

    if (xmlValidator.canAddElement(root, "element")) {
        child = document->createElement("element");

        if (xmlValidator.canAddAttribute(child, "attribute")) {
            attr = document->createAttribute("attribute");
            attr->setValue("attribute value");
            child->setAttributeNode(attr);
        } else {
            std::cout << "Attempted invalid schema operation.\n";
            exit(0);
        }

        root->appendChild(child);
    } else {
        std::cout << "Attempted invalid schema operation.\n";
        exit(0);
    }

    if (xmlValidator.canAddElement(root, "element")) {
        child = document->createElement("element");
        root->appendChild(child);
    } else {
        std::cout << "Attempted invalid schema operation.\n";
        exit(0);
    }

    if (xmlValidator.canAddElement(root, "element")) {
        child = document->createElement("element");

        if (xmlValidator.canAddAttribute(child, "attribute"))
            child->setAttribute("attribute", "attribute value");
        else {
            std::cout << "Attempted invalid schema operation.\n";
            exit(0);
        }

        if (xmlValidator.canAddAttribute(child, "attribute2"))
            child->setAttribute("attribute2", "attribute2 value");
        else {
            std::cout << "Attempted invalid schema operation.\n";
            exit(0);
        }

        if (xmlValidator.canAddText(child)) {
            dom::Text* text = document->createTextNode("Element Value");
            child->appendChild(text);
        } else {
            std::cout << "Attempted invalid schema operation.\n";
            exit(0);
        }

        root->appendChild(child);
    } else {
        std::cout << "Attempted invalid schema operation.\n";
        exit(0);
    }

    if (xmlValidator.canAddElement(root, "element")) {
        child = document->createElement("element");
        root->appendChild(child);
    } else {
        std::cout << "Attempted invalid schema operation.\n";
        exit(0);
    }

    //
    // Serialize
    //
    std::fstream* file = 0;
    XMLSerializer xmlSerializer(
        file = new std::fstream(argv[2], std::ios_base::out));
    xmlSerializer.serializePretty(document);

    // delete child;
    // delete root;
    delete document;

    delete file;
    // delete Document and tree.
}
