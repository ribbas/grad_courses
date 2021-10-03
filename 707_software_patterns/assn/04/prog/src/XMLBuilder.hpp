#ifndef XML_BUILDER_H
#define XML_BUILDER_H

#include "Attr.hpp"
#include "Document.hpp"
#include "Element.hpp"
#include "Node.hpp"
#include "Text.hpp"
#include <vector>

// ConcreteBuilder that can be used to build a DOM tree
class XMLBuilder {
private:
    dom::AbstractDOMFactory* domFactory;
    dom::Document* document;
    std::vector<dom::Element*> elementVec;

public:
    // Concrete DOM factory we'll use is Document_Impl
    XMLBuilder();
    dom::Document* getDocument() {
        return document;
    }
    void beginDocument();
    dom::Element* addElement(dom::Element*, std::string);
    // dom::Element* addElement(dom::Document*, std::string);
    dom::Attr* addAttribute(dom::Element*, std::string, std::string);
    dom::Text* addText(dom::Element*, std::string);
};

// Director for XML Parsing and DOM building. Uses builder passed to it
class XMLDirector {
private:
    XMLBuilder* builder;

public:
    XMLDirector(XMLBuilder* builder) : builder(builder) {}
    // ~XMLParseDirector() {
    //     if (builder != 0)
    //         delete builder;
    // }

    dom::Document* parseFile(std::string fileName);
};
#endif // XML_BUILDER_H