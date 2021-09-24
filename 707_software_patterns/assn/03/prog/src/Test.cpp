#include "Attr.hpp"
#include "Document.hpp"
#include "Element.hpp"
#include "Text.hpp"
#include "XMLSerializer.hpp"
#include "XMLTokenizer.hpp"
#include "XMLValidator.hpp"

#include <stdio.h>

void testTokenizer(int argc, char** argv);
void testSerializer(int argc, char** argv);
void testValidator(int argc, char** argv);

void printUsage() {
    printf("Usage:\n");
    printf("\tTest t [file] ...\n");
    printf("\tTest s [file1] [file2]\n");
    printf("\tTest v [file]\n");
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printUsage();
        exit(0);
    }

    switch (argv[1][0]) {
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

void testTokenizer(int argc, char** argv) {
    dom::Document* document = new Document_Impl;

    dom::Element* element = document->createElement("NewElement");
    dom::Text* text = document->createTextNode("Text Data");
    dom::Attr* attr = document->createAttribute("NewAttribute");

    printf("Element Tag = '%s'\n", element->getTagName().c_str());
    printf("Text Data = '%s'\n", text->getValue().c_str());
    printf("Attr Name = '%s'\n", attr->getName().c_str());

    element->setAttributeNode(attr);
    printf("Element attribute '%s'='%s'\n", element->getTagName().c_str(),
           element->getAttribute("NewAttribute").c_str());

    delete element;
    delete text;
    delete attr;
    delete document;

    for (int i = 2; i < argc; i++) {
        XMLTokenizer tokenizer(argv[i]);

        XMLTokenizer::XMLToken* token = 0;

        printf("File:  '%s'\n", argv[i]);

        do {
            delete token;
            token = tokenizer.getNextToken();

            printf("\tLine %d:  %s = '%s'\n", tokenizer.getLineNumber(),
                   token->toString(),
                   token->getToken().size() == 0 ? ""
                                                 : token->getToken().c_str());

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

    ElementComponent* elementComp = new ElementComponent;
    AttrComponent* attrComp = new AttrComponent;
    TextComponent* textComp = new TextComponent;

    elementComp->setElement(root);
    if (elementComp->validate("element")) {
        root = document->createElement("document");

        document->appendChild(root);
    } else {
        printf("Attempted invalid schema operation.");
        exit(0);
    }

    elementComp->setElement(root);
    if (elementComp->validate("element")) {
        child = document->createElement("element");

        attrComp->setElement(child);
        if (attrComp->validate("attribute")) {
            attr = document->createAttribute("attribute");
            attr->setValue("attribute value");
            child->setAttributeNode(attr);
        } else {
            printf("Attempted invalid schema operation.");
            exit(0);
        }

        root->appendChild(child);
    } else {
        printf("Attempted invalid schema operation.");
        exit(0);
    }

    elementComp->setElement(root);
    if (elementComp->validate("element")) {
        child = document->createElement("element");
        root->appendChild(child);
    } else {
        printf("Attempted invalid schema operation.");
        exit(0);
    }

    elementComp->setElement(root);
    if (elementComp->validate("element")) {
        child = document->createElement("element");

        attrComp->setElement(child);
        if (attrComp->validate("attribute"))
            child->setAttribute("attribute", "attribute value");
        else {
            printf("Attempted invalid schema operation.");
            exit(0);
        }

        attrComp->setElement(child);
        if (attrComp->validate("attribute2"))
            child->setAttribute("attribute2", "attribute2 value");
        else {
            printf("Attempted invalid schema operation.");
            exit(0);
        }

        textComp->setElement(child);
        if (textComp->validate()) {
            dom::Text* text = document->createTextNode("Element Value");
            child->appendChild(text);
        } else {
            printf("Attempted invalid schema operation.");
            exit(0);
        }

        root->appendChild(child);
    } else {
        printf("Attempted invalid schema operation.");
        exit(0);
    }

    elementComp->setElement(root);
    if (elementComp->validate("element")) {
        child = document->createElement("element");
        root->appendChild(child);
    } else {
        printf("Attempted invalid schema operation.");
        exit(0);
    }

    //
    // Serialize
    //
    //
    // Serialize
    //
    std::fstream* file = 0;
    XMLSerializer xmlSerializer(
        file = new std::fstream(argv[2], std::ios_base::out));
    xmlSerializer.serializePretty(document);
    delete file;
    // delete Document and tree.
}
