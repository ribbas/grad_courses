#ifndef XML_BUILDER_HPP
#define XML_BUILDER_HPP

#include "Attr.hpp"
#include "Document.hpp"
#include "Element.hpp"
#include "Subject.hpp"
#include "Text.hpp"

class XMLBuilder : public virtual Subject {
private:
    dom::Document* document;
    dom::Element* currentElement;

    std::string& ltrim(std::string&);
    void trimAttr(std::string&, std::string&);

public:
    XMLBuilder();

    virtual ~XMLBuilder() {}

    void setElement(dom::Element*);
    dom::Element* getElementParent();
    dom::Document* getDocument();
    dom::Element* addElement(std::string);
    dom::Attr* addAttribute(std::string, std::string);
    dom::Text* addText(std::string);
};

#endif // XML_BUILDER_HPP
