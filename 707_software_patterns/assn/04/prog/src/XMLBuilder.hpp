#ifndef XML_BUILDER_H
#define XML_BUILDER_H

#include "Attr.hpp"
#include "Document.hpp"
#include "Element.hpp"
#include "Node.hpp"
#include "Text.hpp"
#include "XMLTokenizer.hpp"

// ConcreteBuilder that can be used to build a DOM tree
class XMLBuilder {
private:
    dom::Document* document;
    dom::Element* currentElement;
    std::string& ltrim(std::string&);

public:
    XMLBuilder();
    void setElement(dom::Element*);
    dom::Element* getElementParent();
    dom::Document* getDocument() {
        return document;
    }
    dom::Element* addElement(std::string);
    dom::Attr* addAttribute(std::string, std::string);
    dom::Text* addText(std::string);
};

class XMLDirector {
private:
    XMLBuilder* factory;
    XMLTokenizer tokenizer;

public:
    XMLDirector(XMLBuilder* builder, std::string fileName)
        : factory(builder), tokenizer(fileName) {}

    void construct();

    dom::Document* getResult() {
        return factory->getDocument();
    }
};
#endif // XML_BUILDER_H