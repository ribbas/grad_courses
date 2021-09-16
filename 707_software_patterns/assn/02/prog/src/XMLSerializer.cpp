#include "XMLSerializer.hpp"

#include "Attr.hpp"
#include "Document.hpp"
#include "Element.hpp"
#include "Text.hpp"

void XMLSerializerStrategy::prettyIndentation() {

    for (int i = 0; i < indentationLevel; i++) {
        file << "\t";
    }
}

void XMLSerializerPretty::serialize(dom::Node* node) {

    if (dynamic_cast<dom::Document*>(node) != 0) {

        file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
        file << "\n";
        serialize(dynamic_cast<dom::Document*>(node)->getDocumentElement());

    } else if (dynamic_cast<dom::Element*>(node) != 0) {

        prettyIndentation();
        file << "<" << dynamic_cast<dom::Element*>(node)->getTagName();

        int attrCount = 0;

        for (dom::NamedNodeMap::iterator i =
                 dynamic_cast<dom::Element*>(node)->getAttributes()->begin();
             i != dynamic_cast<dom::Element*>(node)->getAttributes()->end();
             i++) {
            serialize(*i);
            attrCount++;
        }

        if (attrCount > 0)
            file << " ";

        if (dynamic_cast<dom::Element*>(node)->getChildNodes()->size() == 0) {
            file << "/>";
            file << "\n";
        } else {

            file << ">";
            file << "\n";
            indentationLevel++;

            for (dom::NodeList::iterator i = dynamic_cast<dom::Element*>(node)
                                                 ->getChildNodes()
                                                 ->begin();
                 i != dynamic_cast<dom::Element*>(node)->getChildNodes()->end();
                 i++) {
                if (dynamic_cast<dom::Element*>(*i) != 0 ||
                    dynamic_cast<dom::Text*>(*i) != 0) {
                    serialize(*i);
                }
            }
            indentationLevel--;
            prettyIndentation();
            file << "</"
                 << dynamic_cast<dom::Element*>(node)->getTagName() + ">";
            file << "\n";
        }
    } else if (dynamic_cast<dom::Attr*>(node) != 0) {
        file << " " << dynamic_cast<dom::Attr*>(node)->getName() << "=\""
             << dynamic_cast<dom::Attr*>(node)->getValue() << "\"";
    } else if (dynamic_cast<dom::Text*>(node) != 0) {
        prettyIndentation();
        file << dynamic_cast<dom::Text*>(node)->getData();
        file << "\n";
    }
}

void XMLSerializerMinimal::serialize(dom::Node* node) {

    if (dynamic_cast<dom::Document*>(node) != 0) {

        file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
        serialize(dynamic_cast<dom::Document*>(node)->getDocumentElement());

    } else if (dynamic_cast<dom::Element*>(node) != 0) {

        file << "<" << dynamic_cast<dom::Element*>(node)->getTagName();

        for (dom::NamedNodeMap::iterator i =
                 dynamic_cast<dom::Element*>(node)->getAttributes()->begin();
             i != dynamic_cast<dom::Element*>(node)->getAttributes()->end();
             i++) {
            serialize(*i);
        }
        if (dynamic_cast<dom::Element*>(node)->getChildNodes()->size() == 0) {

            file << "/>";

        } else {

            file << ">";

            for (dom::NodeList::iterator i = dynamic_cast<dom::Element*>(node)
                                                 ->getChildNodes()
                                                 ->begin();
                 i != dynamic_cast<dom::Element*>(node)->getChildNodes()->end();
                 i++)
                if (dynamic_cast<dom::Element*>(*i) != 0 ||
                    dynamic_cast<dom::Text*>(*i) != 0)
                    serialize(*i);

            file << "</"
                 << dynamic_cast<dom::Element*>(node)->getTagName() + ">";
        }

    } else if (dynamic_cast<dom::Attr*>(node) != 0) {

        file << " " << dynamic_cast<dom::Attr*>(node)->getName() << "=\""
             << dynamic_cast<dom::Attr*>(node)->getValue() << "\"";

    } else if (dynamic_cast<dom::Text*>(node) != 0) {
        file << dynamic_cast<dom::Text*>(node)->getData();
    }
}

// void XMLSerializer::serialize(bool minimal, dom::Node* node) {

//     if (dynamic_cast<dom::Document*>(node) != 0) {
//         file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
//         if (!minimal) {
//             file << "\n";
//         }
//         serialize(minimal,
//                   dynamic_cast<dom::Document*>(node)->getDocumentElement());
//     } else if (dynamic_cast<dom::Element*>(node) != 0) {
//         if (!minimal) {
//             prettyIndentation();
//         }
//         file << "<" << dynamic_cast<dom::Element*>(node)->getTagName();

//         int attrCount = 0;

//         for (dom::NamedNodeMap::iterator i =
//                  dynamic_cast<dom::Element*>(node)->getAttributes()->begin();
//              i != dynamic_cast<dom::Element*>(node)->getAttributes()->end();
//              i++) {
//             serialize(minimal, *i);
//             if (!minimal) {
//                 attrCount++;
//             }
//         }

//         if (!minimal) {
//             if (attrCount > 0) {
//                 file << " ";
//             }
//         }

//         if (dynamic_cast<dom::Element*>(node)->getChildNodes()->size() == 0)
//         {
//             file << "/>";
//             if (!minimal) {
//                 file << "\n";
//             }
//         } else {
//             file << ">";
//             if (!minimal) {
//                 file << "\n";
//                 indentationLevel++;
//             }

//             for (dom::NodeList::iterator i =
//             dynamic_cast<dom::Element*>(node)
//                                                  ->getChildNodes()
//                                                  ->begin();
//                  i !=
//                  dynamic_cast<dom::Element*>(node)->getChildNodes()->end();
//                  i++) {
//                 if (dynamic_cast<dom::Element*>(*i) != 0 ||
//                     dynamic_cast<dom::Text*>(*i) != 0) {
//                     serialize(minimal, *i);
//                 }
//             }
//             if (!minimal) {
//                 indentationLevel--;
//                 prettyIndentation();
//             }
//             file << "</"
//                  << dynamic_cast<dom::Element*>(node)->getTagName() + ">";
//             if (!minimal) {
//                 file << "\n";
//             }
//         }
//     } else if (dynamic_cast<dom::Attr*>(node) != 0) {
//         file << " " << dynamic_cast<dom::Attr*>(node)->getName() << "=\""
//              << dynamic_cast<dom::Attr*>(node)->getValue() << "\"";
//     } else if (dynamic_cast<dom::Text*>(node) != 0) {
//         if (!minimal) {
//             prettyIndentation();
//         }
//         file << dynamic_cast<dom::Text*>(node)->getData();
//         if (!minimal) {
//             file << "\n";
//         }
//     }
// }
