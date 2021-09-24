#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

#include "Node.hpp"

namespace dom {
class Element;
class Text;
class Attr;
class NodeList;

class Document : public virtual Node {
public:
    //
    // Serialization Data Extraction Strategy
    //
    virtual void serialize(std::fstream*, WhitespaceStrategy*) = 0;
    virtual Element* createElement(const std::string&) = 0;
    virtual Text* createTextNode(const std::string&) = 0;
    virtual Attr* createAttribute(const std::string&) = 0;
    virtual Element* getDocumentElement() = 0;
};
}; // namespace dom

class Document_Impl : public virtual dom::Document, public virtual Node_Impl {

public:
    Document_Impl();

    virtual ~Document_Impl();
    //
    // Serialization Data Extraction Strategy
    //
    virtual void serialize(std::fstream*, WhitespaceStrategy*);

    virtual dom::Element* createElement(const std::string&);
    virtual dom::Text* createTextNode(const std::string&);
    virtual dom::Attr* createAttribute(const std::string&);
    virtual dom::Element* getDocumentElement();
};

#endif // DOCUMENT_H
