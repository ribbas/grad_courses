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
void XMLSerializerContext::setStrategy(XMLSerializerStrategy* strategy) {
    delete this->strategy_;
    this->strategy_ = strategy;
}

XMLSerializerStrategy::XMLSerializerStrategy(const std::string& filename,
                                             const std::string& newline)
    : indentationLevel(0), file(filename.c_str(), std::ios_base::out),
      newline(newline) {
    domSerializerContext = new DOMSerializerContext();
}

void XMLSerializerStrategy::serialize(dom::Node* node) {

    domSerializerContext->findNodeType(node, this);
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

DOMSerializerContext::DOMSerializerContext(DOMSerializerStrategy* strategy)
    : strategy_(strategy) {}

void DOMSerializerContext::setStrategy(DOMSerializerStrategy* strategy) {
    if (this->strategy_) {
        delete this->strategy_;
    }
    this->strategy_ = strategy;
}

void DOMSerializerContext::findNodeType(
    dom::Node* node, XMLSerializerStrategy* xmlSerializerStrategy) {

    if (dynamic_cast<dom::Document*>(node) != 0) {
        setStrategy(new DocumentSerializer(node, xmlSerializerStrategy));

    } else if (dynamic_cast<dom::Element*>(node) != 0) {
        setStrategy(new ElementSerializer(node, xmlSerializerStrategy));

    } else if (dynamic_cast<dom::Attr*>(node) != 0) {
        setStrategy(new AttrSerializer(node, xmlSerializerStrategy));

    } else if (dynamic_cast<dom::Text*>(node) != 0) {
        setStrategy(new TextSerializer(node, xmlSerializerStrategy));
    }
}

DocumentSerializer::DocumentSerializer(
    dom::Node* node, XMLSerializerStrategy* xmlSerializerStrategy)
    : DOMSerializerStrategy(node) {

    xmlSerializerStrategy->file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>"
                                << xmlSerializerStrategy->newline;
    xmlSerializerStrategy->serialize(
        dynamic_cast<dom::Document*>(node)->getDocumentElement());
}

ElementSerializer::ElementSerializer(
    dom::Node* node, XMLSerializerStrategy* xmlSerializerStrategy)
    : DOMSerializerStrategy(node) {

    xmlSerializerStrategy->prettyIndentation();
    xmlSerializerStrategy->file
        << "<" << dynamic_cast<dom::Element*>(node)->getTagName();

    int attrCount = 0;

    for (dom::NamedNodeMap::iterator i =
             dynamic_cast<dom::Element*>(node)->getAttributes()->begin();
         i != dynamic_cast<dom::Element*>(node)->getAttributes()->end(); i++) {

        xmlSerializerStrategy->serialize(*i);
        attrCount++;
    }

    if (attrCount > 0) {

        xmlSerializerStrategy->multipleAttr();
    }

    if (dynamic_cast<dom::Element*>(node)->getChildNodes()->size() == 0) {

        xmlSerializerStrategy->file << "/>" << xmlSerializerStrategy->newline;

    } else {

        xmlSerializerStrategy->file << ">" << xmlSerializerStrategy->newline;
        xmlSerializerStrategy->indentationLevel++;

        for (dom::NodeList::iterator i =
                 dynamic_cast<dom::Element*>(node)->getChildNodes()->begin();
             i != dynamic_cast<dom::Element*>(node)->getChildNodes()->end();
             i++) {
            if (dynamic_cast<dom::Element*>(*i) != 0 ||
                dynamic_cast<dom::Text*>(*i) != 0) {
                xmlSerializerStrategy->serialize(*i);
            }
        }

        xmlSerializerStrategy->indentationLevel--;
        xmlSerializerStrategy->prettyIndentation();
        xmlSerializerStrategy->file
            << "</" << dynamic_cast<dom::Element*>(node)->getTagName() << ">"
            << xmlSerializerStrategy->newline;
    }
}

AttrSerializer::AttrSerializer(dom::Node* node,
                               XMLSerializerStrategy* xmlSerializerStrategy)
    : DOMSerializerStrategy(node) {
    xmlSerializerStrategy->file
        << " " << dynamic_cast<dom::Attr*>(node)->getName() << "=\""
        << dynamic_cast<dom::Attr*>(node)->getValue() << "\"";
}

TextSerializer::TextSerializer(dom::Node* node,
                               XMLSerializerStrategy* xmlSerializerStrategy)
    : DOMSerializerStrategy(node) {
    xmlSerializerStrategy->prettyIndentation();
    xmlSerializerStrategy->file << dynamic_cast<dom::Text*>(node)->getData()
                                << xmlSerializerStrategy->newline;
}
