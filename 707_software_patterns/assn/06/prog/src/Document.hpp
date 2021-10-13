#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "Iterator.hpp"
#include "Node.hpp"

namespace dom {

class Element;
class Text;
class Attr;
class NodeList;
class Iterator;

class Document : public virtual Node {
public:
    virtual Element* createElement(const std::string&) = 0;
    virtual Text* createTextNode(const std::string&) = 0;
    virtual Attr* createAttribute(const std::string&) = 0;
    virtual Element* getDocumentElement() = 0;
    virtual Iterator* createIterator() = 0;
    virtual void serialize(std::fstream*, WhitespaceStrategy*) = 0;
};
}; // namespace dom

class Document_Impl : public virtual dom::Document, public virtual Node_Impl {

public:
    Document_Impl();
    virtual ~Document_Impl();

    virtual dom::Element* createElement(const std::string&) override;
    virtual dom::Text* createTextNode(const std::string&) override;
    virtual dom::Attr* createAttribute(const std::string&) override;
    virtual dom::Element* getDocumentElement() override;
    virtual dom::Iterator* createIterator() override;
    virtual void serialize(std::fstream*, WhitespaceStrategy*) override;
};

#endif // DOCUMENT_H
