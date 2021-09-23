
#include "XMLSerializer.hpp"

#include "Attr.hpp"
#include "Document.hpp"
#include "Element.hpp"
#include "Text.hpp"

void XMLSerializer::prettyIndentation() {
    for (int i = 0; i < indentationLevel; i++) {
        file << "\t";
    }
}

void XMLSerializer::serialize(dom::Node* node) {
    if (dynamic_cast<dom::Document*>(node) != 0) {
        serializeDocument(node);
    } else if (dynamic_cast<dom::Element*>(node) != 0) {
        serializeElement(node);
    } else if (dynamic_cast<dom::Attr*>(node) != 0) {
        serializeAttr(node);
    } else if (dynamic_cast<dom::Text*>(node) != 0) {
        serializeText(node);
    }
}

void XMLSerializer::serializeDocument(dom::Node* node) {
    file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
    file << "\n";
}

void XMLSerializer::serializeElement(dom::Node* node) {

    prettyIndentation();
    file << "<" << dynamic_cast<dom::Element*>(node)->getNodeName();

    int attrCount = 0;

    for (dom::NamedNodeMap::iterator i =
             dynamic_cast<dom::Element*>(node)->getAttributes()->begin();
         i != dynamic_cast<dom::Element*>(node)->getAttributes()->end(); i++) {
        serialize(*i);
        attrCount++;
    }

    if (attrCount > 0) {
        file << " ";
    }

    if (dynamic_cast<dom::Element*>(node)->getChildNodes()->size() == 0) {
        file << "/>";
        file << "\n";

    } else {

        file << ">";
        file << "\n";
        indentationLevel++;

        for (dom::NodeList::iterator i =
                 dynamic_cast<dom::Element*>(node)->getChildNodes()->begin();
             i != dynamic_cast<dom::Element*>(node)->getChildNodes()->end();
             i++) {
            if (dynamic_cast<dom::Element*>(*i) != 0 ||
                dynamic_cast<dom::Text*>(*i) != 0) {
                serialize(*i);
                // serializePretty(*i);
            }
        }

        indentationLevel--;
        prettyIndentation();
        file << "</" << dynamic_cast<dom::Element*>(node)->getNodeName() + ">";
        file << "\n";
    }
}

void XMLSerializer::serializeAttr(dom::Node* node) {

    file << " " << dynamic_cast<dom::Attr*>(node)->getNodeName() << "=\""
         << dynamic_cast<dom::Attr*>(node)->getNodeValue() << "\"";
}

void XMLSerializer::serializeText(dom::Node* node) {
    prettyIndentation();
    file << dynamic_cast<dom::Text*>(node)->getNodeValue();
    file << "\n";
}

void XMLSerializer::serializePretty(dom::Node* node) {

    DocumentContainer docContainer;
    docContainer.containerize(node);

    XMLSerializerIterator<DocumentContainer>* it =
        docContainer.createIterator();

    for (it->begin(); !it->end(); it->next()) {

        std::cout << "hey " << *it->data() << std::endl;
        serialize(*it->data());
    }
}

void XMLSerializer::serializeMinimal(dom::Node* node) {
    if (dynamic_cast<dom::Document*>(node) != 0) {
        file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
        serializeMinimal(
            dynamic_cast<dom::Document*>(node)->getDocumentElement());
    } else if (dynamic_cast<dom::Element*>(node) != 0) {
        file << "<" << dynamic_cast<dom::Element*>(node)->getNodeName();

        for (dom::NamedNodeMap::iterator i =
                 dynamic_cast<dom::Element*>(node)->getAttributes()->begin();
             i != dynamic_cast<dom::Element*>(node)->getAttributes()->end();
             i++)
            serializeMinimal(*i);

        if (dynamic_cast<dom::Element*>(node)->getChildNodes()->size() == 0)
            file << "/>";
        else {
            file << ">";

            for (dom::NodeList::iterator i = dynamic_cast<dom::Element*>(node)
                                                 ->getChildNodes()
                                                 ->begin();
                 i != dynamic_cast<dom::Element*>(node)->getChildNodes()->end();
                 i++)
                if (dynamic_cast<dom::Element*>(*i) != 0 ||
                    dynamic_cast<dom::Text*>(*i) != 0)
                    serializeMinimal(*i);

            file << "</"
                 << dynamic_cast<dom::Element*>(node)->getNodeName() + ">";
        }
    } else if (dynamic_cast<dom::Attr*>(node) != 0) {
        file << " " << dynamic_cast<dom::Attr*>(node)->getNodeName() << "=\""
             << dynamic_cast<dom::Attr*>(node)->getNodeValue() << "\"";
    } else if (dynamic_cast<dom::Text*>(node) != 0)
        file << dynamic_cast<dom::Text*>(node)->getNodeValue();
}
