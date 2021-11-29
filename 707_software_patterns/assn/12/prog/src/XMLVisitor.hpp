#ifndef XML_VISITOR_HPP
#define XML_VISITOR_HPP

namespace dom {
class Document;
class Element;
class Attr;
class Text;
}; // namespace dom

class XMLVisitor {
public:
    virtual void visitDocument(dom::Document*) = 0;
    virtual void visitElement(dom::Element*) = 0;
    virtual void visitAttr(dom::Attr*) = 0;
    virtual void visitText(dom::Text*) = 0;
};

#endif // XML_VISITOR_HPP
