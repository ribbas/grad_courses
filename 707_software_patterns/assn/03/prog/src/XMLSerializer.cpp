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
            // if (dynamic_cast<dom::Document*>(i) != 0) {
            //     std::cout << "Document " << i << std::endl;
            // } else if (dynamic_cast<dom::Element*>(i) != 0) {
            //     std::cout << "Element " << i << std::endl;
            // } else if (dynamic_cast<dom::Attr*>(i) != 0) {
            //     std::cout << "Attr " << i << std::endl;
            // } else if (dynamic_cast<dom::Text*>(i) != 0) {
            //     std::cout << "Text " << i << std::endl;
            // }
            // std::cout << i << std::endl;
            if (dynamic_cast<dom::Element*>(i) != 0) {

                m_data_.push_back(i);
                for (dom::NamedNodeMap::iterator j =
                         dynamic_cast<dom::Element*>(i)
                             ->getAttributes()
                             ->begin();
                     j !=
                     dynamic_cast<dom::Element*>(i)->getAttributes()->end();
                     j++) {
                    m_data_.push_back(*j);
                }

                if (dynamic_cast<dom::Element*>(i)->getChildNodes()->size()) {

                    for (dom::NodeList::iterator j =
                             dynamic_cast<dom::Element*>(i)
                                 ->getChildNodes()
                                 ->begin();
                         j !=
                         dynamic_cast<dom::Element*>(i)->getChildNodes()->end();
                         j++) {
                        if (dynamic_cast<dom::Element*>(*j) != 0 ||
                            dynamic_cast<dom::Text*>(*j) != 0) {
                            m_data_.push_back(*j);
                        }
                    }
                }
            } else {
                m_data_.push_back(i);
            }
            containerize(i, false);
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
        // serialize(*i);
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
                // serialize(*i);
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

        if (dynamic_cast<dom::Element*>(node)->getChildNodes()->size() == 0) {
            file << "/>";
        } else {
            file << ">";

            for (dom::NodeList::iterator i = dynamic_cast<dom::Element*>(node)
                                                 ->getChildNodes()
                                                 ->begin();
                 i != dynamic_cast<dom::Element*>(node)->getChildNodes()->end();
                 i++) {
                if (dynamic_cast<dom::Element*>(*i) != 0 ||
                    dynamic_cast<dom::Text*>(*i) != 0) {
                    serializeMinimal(*i);
                }
            }

            file << "</"
                 << dynamic_cast<dom::Element*>(node)->getNodeName() + ">";
        }
    } else if (dynamic_cast<dom::Attr*>(node) != 0) {
        file << " " << dynamic_cast<dom::Attr*>(node)->getNodeName() << "=\""
             << dynamic_cast<dom::Attr*>(node)->getNodeValue() << "\"";
    } else if (dynamic_cast<dom::Text*>(node) != 0) {
        file << dynamic_cast<dom::Text*>(node)->getNodeValue();
    }
}
