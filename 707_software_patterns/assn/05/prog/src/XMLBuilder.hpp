#ifndef XML_BUILDER_H
#define XML_BUILDER_H

#include "Attr.hpp"
#include "Document.hpp"
#include "Element.hpp"
#include "Text.hpp"

class XMLDirector;

class XMLBuilder {
private:
    dom::Document* document;
    dom::Element* currentElement;
    static XMLBuilder* singleton;

    std::string& ltrim(std::string&);
    void trimAttr(std::string&, std::string&);

    XMLBuilder();

public:
    static XMLBuilder* getInstance();

    void setElement(dom::Element*);
    dom::Element* getElementParent();
    dom::Document* getDocument();
    dom::Element* addElement(std::string, int = 0, XMLDirector* = nullptr);
    dom::Attr* addAttribute(std::string, std::string);
    dom::Text* addText(std::string);
};

#endif // XML_BUILDER_H
