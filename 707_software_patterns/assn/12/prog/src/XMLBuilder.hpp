#ifndef XML_BUILDER_HPP
#define XML_BUILDER_HPP

#include "Attr.hpp"
#include "Document.hpp"
#include "Element.hpp"
#include "Text.hpp"

class XMLBuilder {
private:
    dom::Document* document;
    dom::Element* currentElement;
    std::string attrName;

    std::string& ltrim(std::string&);
    void trimAttr(std::string&, std::string&);

public:
    XMLBuilder();

    void setElement(dom::Element*);
    dom::Element* getElementParent();
    dom::Document* getDocument();
    dom::Element* addElement(std::string);
    dom::Element* getElement();
    // dom::Attr* addAttribute(std::string, std::string);
    void addAttrName(std::string);
    dom::Attr* addAttrValue(std::string);
    dom::Text* addText(std::string);
};

#endif // XML_BUILDER_HPP
