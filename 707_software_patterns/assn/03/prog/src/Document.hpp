#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

#include "Node.hpp"

namespace dom {
class Element;
class Text;
class Attr;
class NodeList;
class DocumentNodeFactory;

class Document : public virtual Node {
public:
    virtual Element* createElement(const std::string&) = 0;
    virtual Text* createTextNode(const std::string&) = 0;
    virtual Attr* createAttribute(const std::string&) = 0;
    virtual Element* getDocumentElement() = 0;
};
}; // namespace dom

class DocumentNodeFactory;
class Document_Impl : public virtual dom::Document, public virtual Node_Impl {
private:
    DocumentNodeFactory* documentNodeFactory;

public:
    Document_Impl();

    virtual ~Document_Impl();

    virtual dom::Element* createElement(const std::string&);
    virtual dom::Text* createTextNode(const std::string&);
    virtual dom::Attr* createAttribute(const std::string&);
    virtual dom::Element* getDocumentElement();
};

class DocumentNodeFactory : public virtual dom::Document,
                            public virtual Node_Impl {
public:
    DocumentNodeFactory();
    dom::Node* createDocumentNode(dom::Document* document, int nodeType,
                                  const std::string& value);
};

#endif // DOCUMENT_H
