#include "Test.hpp"

void testValidator(int argc, char** argv) {
    if (argc < 3) {
        printUsage();
        return;
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

    std::cout << "Saving validator\n";
    xmlValidator.save();

    schemaElement->addValidChild("attribute3", true);

    dom::Document* document = new Document_Impl;
    dom::Element* root = nullptr;
    dom::Element* child = nullptr;
    dom::Attr* attr = nullptr;

    if (xmlValidator.canRootElement("document")) {
        root = document->createElement("document");
        document->appendChild(root);
    } else {
        printf("Attempted invalid schema operation.");
        return;
    }

    if (xmlValidator.canAddElement(root, "element")) {
        child = document->createElement("element");

        if (xmlValidator.canAddAttribute(child, "attribute")) {
            attr = document->createAttribute("attribute");
            attr->setValue("attribute value");
            child->setAttributeNode(attr);
        } else {
            printf("Attempted invalid schema operation.");
            return;
        }

        root->appendChild(child);
    } else {
        printf("Attempted invalid schema operation.");
        return;
    }

    if (xmlValidator.canAddElement(root, "element")) {
        child = document->createElement("element");
        root->appendChild(child);
    } else {
        printf("Attempted invalid schema operation.");
        return;
    }

    if (xmlValidator.canAddElement(root, "element")) {
        child = document->createElement("element");

        if (xmlValidator.canAddAttribute(child, "attribute"))
            child->setAttribute("attribute", "attribute value");
        else {
            printf("Attempted invalid schema operation.");
            return;
        }

        if (xmlValidator.canAddAttribute(child, "attribute2"))
            child->setAttribute("attribute2", "attribute2 value");
        else {
            printf("Attempted invalid schema operation.");
            return;
        }

        if (xmlValidator.canAddAttribute(child, "attribute3"))
            child->setAttribute("attribute3", "attribute3 value");
        else {
            printf("Attempted invalid schema operation.");
            return;
        }

        if (xmlValidator.canAddText(child)) {
            dom::Text* text = document->createTextNode("Element Value");
            child->appendChild(text);
        } else {
            printf("Attempted invalid schema operation.");
            return;
        }

        root->appendChild(child);
    } else {
        printf("Attempted invalid schema operation.");
        return;
    }

    if (xmlValidator.canAddElement(root, "element")) {
        child = document->createElement("element");
        root->appendChild(child);
    } else {
        printf("Attempted invalid schema operation.");
        return;
    }

    xmlValidator.undo();
    std::cout << "Reverted validator\n";
    if (xmlValidator.canAddAttribute(child, "attribute3"))
        child->setAttribute("attribute3", "attribute3 value");
    else {
        printf("Attempted invalid schema operation.");
        return;
    }

    //
    // Serialize
    //
    std::fstream* file = nullptr;
    XMLSerializer xmlSerializer(
        file = new std::fstream(argv[2], std::ios_base::out));
    xmlSerializer.serializePretty();
    document->accept(&xmlSerializer);

    delete document;
    delete file;
}
