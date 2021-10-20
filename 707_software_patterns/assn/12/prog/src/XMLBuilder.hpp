#ifndef XML_BUILDER_H
#define XML_BUILDER_H

#include "Attr.hpp"
#include "Document.hpp"
#include "Element.hpp"
#include "Text.hpp"

class XMLBuilder {
private:
    dom::Document* document;
    dom::Element* currentElement;

    std::string& ltrim(std::string&);
    void trimAttr(std::string&, std::string&);

public:
    XMLBuilder();

    void setElement(dom::Element*);
    dom::Element* getElementParent();
    dom::Document* getDocument();
    dom::Element* addElement(std::string);
    dom::Attr* addAttribute(std::string, std::string);
    dom::Text* addText(std::string);
};

#endif // XML_BUILDER_H