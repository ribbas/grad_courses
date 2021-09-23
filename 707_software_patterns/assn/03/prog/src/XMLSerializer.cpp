#include <set>
#include <stack>

#include "XMLSerializer.hpp"

#include "Attr.hpp"
#include "Document.hpp"
#include "Element.hpp"
#include "Text.hpp"

void DocumentContainer::containerize(dom::Node* document, bool init) {

    if (init) {
        m_data_.push_back(document);
    }

    if (dynamic_cast<dom::Document*>(document) != 0) {
        std::cout << "Document " << document << std::endl;
    } else if (dynamic_cast<dom::Element*>(document) != 0) {
        std::cout << "Element " << document << std::endl;
    } else if (dynamic_cast<dom::Attr*>(document) != 0) {
        std::cout << "Attr " << document << std::endl;
    } else if (dynamic_cast<dom::Text*>(document) != 0) {
        std::cout << "Text " << document << std::endl;
    }

    if (document->hasChildNodes()) {
        for (auto i : *document->getChildNodes()) {
            m_data_.push_back(i);
        }
    }
}

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

        // std::cout << "hey " << *it->data() << std::endl;
        serialize(*it->data());
    }
}

// doc
// ele
// ele
// att
// ele
// ele
// att
// att
// tex
// ele

void XMLSerializer::serializeMinimal(dom::Node* node) {

    std::stack<dom::Node*> nodeStack;
    dom::Node* cur;
    nodeStack.push(node);

    dom::NamedNodeMap::iterator iter, iter2;
    bool init = true;
    bool init2 = true;
    std::set<dom::Node*> l;

    while (nodeStack.size()) {

        std::cout << "size " << nodeStack.size() << '\n';
        cur = nodeStack.top();
        nodeStack.pop();
        std::cout << "grabbing " << cur << '\n';

        if (dynamic_cast<dom::Document*>(cur) != 0) {

            std::cout << "doc\n";

            file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
            nodeStack.push(
                dynamic_cast<dom::Document*>(cur)->getDocumentElement());

        } else if (dynamic_cast<dom::Element*>(cur) != 0) {
            std::cout << "ele\n";

            file << "<" << dynamic_cast<dom::Element*>(cur)->getNodeName();

            if (dynamic_cast<dom::Element*>(cur)->getAttributes()->size() !=
                0) {
                if (iter !=
                    dynamic_cast<dom::Element*>(cur)->getAttributes()->end()) {

                    if (iter != dynamic_cast<dom::Element*>(cur)
                                    ->getAttributes()
                                    ->begin() &&
                        init) {
                        iter = dynamic_cast<dom::Element*>(cur)
                                   ->getAttributes()
                                   ->begin();
                        init = false;
                        std::cout << *iter << '\n';
                    }
                    std::cout << "pushing " << *iter << '\n';
                    nodeStack.push(*iter);
                    iter++;
                    continue;
                }
            }

            if (dynamic_cast<dom::Element*>(cur)->getChildNodes()->size() ==
                0) {
                file << "/>";
            } else {
                file << ">";
                std::cout << "hmm?\n";

                if (iter2 !=
                    dynamic_cast<dom::Element*>(cur)->getChildNodes()->end()) {

                    if (iter2 != dynamic_cast<dom::Element*>(cur)
                                     ->getChildNodes()
                                     ->begin() &&
                        init2) {
                        iter2 = dynamic_cast<dom::Element*>(cur)
                                    ->getChildNodes()
                                    ->begin();
                        init2 = false;
                    }
                    if (dynamic_cast<dom::Element*>(*iter2) != 0 ||
                        dynamic_cast<dom::Text*>(*iter2) != 0) {
                        nodeStack.push(*iter2);
                    }
                    iter2++;
                    continue;
                }

                std::cout << "hello?\n";
                file << "</"
                     << dynamic_cast<dom::Element*>(cur)->getNodeName() + ">";
            }
        } else if (dynamic_cast<dom::Attr*>(cur) != 0) {
            std::cout << "att\n";

            file << " " << dynamic_cast<dom::Attr*>(cur)->getNodeName() << "=\""
                 << dynamic_cast<dom::Attr*>(cur)->getNodeValue() << "\"";
            nodeStack.push(cur->getParentNode());

        } else if (dynamic_cast<dom::Text*>(cur) != 0) {
            std::cout << "tex\n";

            file << dynamic_cast<dom::Text*>(cur)->getNodeValue();
            nodeStack.push(cur->getParentNode());
        } else {
            std::cout << "NODNOSNDS\n";
        }
    }
}

// void XMLSerializer::serializeMinimal(dom::Node* node) {

//     if (dynamic_cast<dom::Document*>(node) != 0) {
//         std::cout << "doc\n";
//         file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
//         serializeMinimal(
//             dynamic_cast<dom::Document*>(node)->getDocumentElement());
//     } else if (dynamic_cast<dom::Element*>(node) != 0) {
//         std::cout << "ele\n";
//         file << "<" << dynamic_cast<dom::Element*>(node)->getNodeName();

//         std::cout << "size "
//                   <<
//                   dynamic_cast<dom::Element*>(node)->getAttributes()->size()
//                   << '\n';
//         for (dom::NamedNodeMap::iterator i =
//                  dynamic_cast<dom::Element*>(node)->getAttributes()->begin();
//              i != dynamic_cast<dom::Element*>(node)->getAttributes()->end();
//              i++) {
//             serializeMinimal(*i);
//         }

//         if (dynamic_cast<dom::Element*>(node)->getChildNodes()->size() == 0)
//         {
//             file << "/>";
//         } else {
//             file << ">";

//             for (dom::NodeList::iterator i =
//             dynamic_cast<dom::Element*>(node)
//                                                  ->getChildNodes()
//                                                  ->begin();
//                  i !=
//                  dynamic_cast<dom::Element*>(node)->getChildNodes()->end();
//                  i++) {
//                 if (dynamic_cast<dom::Element*>(*i) != 0 ||
//                     dynamic_cast<dom::Text*>(*i) != 0) {
//                     serializeMinimal(*i);
//                 }
//             }

//             file << "</"
//                  << dynamic_cast<dom::Element*>(node)->getNodeName() + ">";
//         }
//     } else if (dynamic_cast<dom::Attr*>(node) != 0) {
//         std::cout << "att\n";
//         file << " " << dynamic_cast<dom::Attr*>(node)->getNodeName() << "=\""
//              << dynamic_cast<dom::Attr*>(node)->getNodeValue() << "\"";
//     } else if (dynamic_cast<dom::Text*>(node) != 0) {
//         std::cout << "tex\n";
//         file << dynamic_cast<dom::Text*>(node)->getNodeValue();
//     }
// }
