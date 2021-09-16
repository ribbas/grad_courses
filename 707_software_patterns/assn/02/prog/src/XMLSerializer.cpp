#include "XMLSerializer.hpp"

#include "Attr.hpp"
#include "Document.hpp"
#include "Element.hpp"
#include "Text.hpp"

XMLSerializerContext::XMLSerializerContext(XMLSerializerStrategy* strategy)
    : strategy_(strategy) {}

XMLSerializerContext::~XMLSerializerContext() {
    delete this->strategy_;
}

void XMLSerializerContext::serialize(dom::Node* node) {
    this->strategy_->serialize(node);
}

/**
 * Usually, the XMLSerializerContext allows replacing a Strategy object at
 * runtime.
 */
void XMLSerializerContext::set_strategy(XMLSerializerStrategy* strategy) {
    delete this->strategy_;
    this->strategy_ = strategy;
}

XMLSerializerStrategy::XMLSerializerStrategy(const std::string& filename,
                                             const std::string& newline)
    : indentationLevel(0), file(filename.c_str(), std::ios_base::out),
      newline(newline) {}

void XMLSerializerStrategy::serialize(dom::Node* node) {

    if (dynamic_cast<dom::Document*>(node) != 0) {

        file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>" << newline;
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

        if (attrCount > 0) {

            multipleAttr();
        }

        if (dynamic_cast<dom::Element*>(node)->getChildNodes()->size() == 0) {

            file << "/>" << newline;

        } else {

            file << ">" << newline;
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
                 << dynamic_cast<dom::Element*>(node)->getTagName() + ">"
                 << newline;
        }

    } else if (dynamic_cast<dom::Attr*>(node) != 0) {

        file << " " << dynamic_cast<dom::Attr*>(node)->getName() << "=\""
             << dynamic_cast<dom::Attr*>(node)->getValue() << "\"";

    } else if (dynamic_cast<dom::Text*>(node) != 0) {
        prettyIndentation();
        file << dynamic_cast<dom::Text*>(node)->getData() << newline;
    }
}

XMLSerializerPretty::XMLSerializerPretty(const std::string& filename)
    : XMLSerializerStrategy(filename, "\n") {}

void XMLSerializerPretty::prettyIndentation() {

    for (int i = 0; i < indentationLevel; i++) {
        file << "\t";
    }
}

void XMLSerializerPretty::multipleAttr() {

    file << " ";
}

XMLSerializerMinimal::XMLSerializerMinimal(const std::string& filename)
    : XMLSerializerStrategy(filename, "") {}

void XMLSerializerMinimal::prettyIndentation() {}

void XMLSerializerMinimal::multipleAttr() {}
