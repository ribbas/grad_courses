
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

void XMLSerializer::serializePretty(dom::Node* node) {

    DocumentContainer docContainer;
    docContainer.containerize(node);

    XMLSerializerIterator<DocumentContainer>* it =
        docContainer.CreateIterator();

    for (it->begin(); !it->end(); it->next()) {

        if (dynamic_cast<dom::Element*>(*it->Current()) != 0) {
            std::cout << "LOL BRO " << *it->Current() << std::endl;
        }
        std::cout << "hey " << *it->Current() << std::endl;

        // if (dynamic_cast<dom::Document*>(*it->Current()) != 0) {
        //     file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
        //     file << "\n";
        // } else if (dynamic_cast<dom::Element*>(*it->Current()) != 0) {
        //     prettyIndentation();
        //     file << "<"
        //          <<
        //          dynamic_cast<dom::Element*>(*it->Current())->getNodeName();

        //     int attrCount = 0;

        //     for (dom::NamedNodeMap::iterator i =
        //              dynamic_cast<dom::Element*>(*it->Current())
        //                  ->getAttributes()
        //                  ->begin();
        //          i != dynamic_cast<dom::Element*>(*it->Current())
        //                   ->getAttributes()
        //                   ->end();
        //          i++) {
        //         // serializePretty(*i);
        //         attrCount++;
        //     }

        //     if (attrCount > 0) {
        //         file << " ";
        //     }

        //     if (dynamic_cast<dom::Element*>(*it->Current())
        //             ->getChildNodes()
        //             ->size() == 0) {
        //         file << "/>";
        //         file << "\n";

        //     } else {

        //         file << ">";
        //         file << "\n";
        //         indentationLevel++;

        //         for (dom::NodeList::iterator i =
        //                  dynamic_cast<dom::Element*>(*it->Current())
        //                      ->getChildNodes()
        //                      ->begin();
        //              i != dynamic_cast<dom::Element*>(*it->Current())
        //                       ->getChildNodes()
        //                       ->end();
        //              i++) {
        //             if (dynamic_cast<dom::Element*>(*i) != 0 ||
        //                 dynamic_cast<dom::Text*>(*i) != 0) {
        //                 // serializePretty(*i);
        //             }
        //         }

        //         indentationLevel--;
        //         prettyIndentation();
        //         file << "</"
        //              << dynamic_cast<dom::Element*>(*it->Current())
        //                         ->getNodeName() +
        //                     ">";
        //         file << "\n";
        //     }

        // } else if (dynamic_cast<dom::Attr*>(*it->Current()) != 0) {
        //     file << " "
        //          << dynamic_cast<dom::Attr*>(*it->Current())->getNodeName()
        //          << "=\""
        //          << dynamic_cast<dom::Attr*>(*it->Current())->getNodeValue()
        //          << "\"";

        // } else if (dynamic_cast<dom::Text*>(*it->Current()) != 0) {
        //     prettyIndentation();
        //     file << dynamic_cast<dom::Text*>(*it->Current())->getNodeValue();
        //     file << "\n";
        // }
    }

    // if (dynamic_cast<dom::Document*>(node) != 0) {
    //     file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
    //     file << "\n";
    //     serializePretty(
    //         dynamic_cast<dom::Document*>(node)->getDocumentElement());
    // } else if (dynamic_cast<dom::Element*>(node) != 0) {
    //     prettyIndentation();
    //     file << "<" << dynamic_cast<dom::Element*>(node)->getNodeName();

    //     int attrCount = 0;

    //     for (dom::NamedNodeMap::iterator i =
    //              dynamic_cast<dom::Element*>(node)->getAttributes()->begin();
    //          i != dynamic_cast<dom::Element*>(node)->getAttributes()->end();
    //          i++) {
    //         serializePretty(*i);
    //         attrCount++;
    //     }

    //     if (attrCount > 0) {
    //         file << " ";
    //     }

    //     if (dynamic_cast<dom::Element*>(node)->getChildNodes()->size() == 0)
    //     {
    //         file << "/>";
    //         file << "\n";

    //     } else {

    //         file << ">";
    //         file << "\n";
    //         indentationLevel++;

    //         for (dom::NodeList::iterator i =
    //         dynamic_cast<dom::Element*>(node)
    //                                              ->getChildNodes()
    //                                              ->begin();
    //              i !=
    //              dynamic_cast<dom::Element*>(node)->getChildNodes()->end();
    //              i++) {
    //             if (dynamic_cast<dom::Element*>(*i) != 0 ||
    //                 dynamic_cast<dom::Text*>(*i) != 0) {
    //                 serializePretty(*i);
    //             }
    //         }

    //         indentationLevel--;
    //         prettyIndentation();
    //         file << "</"
    //              << dynamic_cast<dom::Element*>(node)->getNodeName() + ">";
    //         file << "\n";
    //     }

    // } else if (dynamic_cast<dom::Attr*>(node) != 0) {
    //     file << " " << dynamic_cast<dom::Attr*>(node)->getNodeName() << "=\""
    //          << dynamic_cast<dom::Attr*>(node)->getNodeValue() << "\"";

    // } else if (dynamic_cast<dom::Text*>(node) != 0) {
    //     prettyIndentation();
    //     file << dynamic_cast<dom::Text*>(node)->getNodeValue();
    //     file << "\n";
    // }
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
