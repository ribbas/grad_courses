#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "Node.hpp"

namespace dom {
class Document;

class Text : public virtual Node {
public:
    virtual ~Text() {}

    virtual void serialize(std::fstream*, WhitespaceStrategy*) = 0;
    virtual const std::string& getName() = 0;
    virtual const std::string& getData() = 0;
    virtual const std::string& getValue() = 0;
    virtual void setData(const std::string&) = 0;
    virtual void setValue(const std::string&) = 0;
    virtual int getLength() = 0;
    virtual const std::string& substringData(int, int) = 0;
    virtual void appendData(const std::string&) = 0;
    virtual void insertData(int, const std::string&) = 0;
    virtual void deleteData(int, int) = 0;
    virtual void replaceData(int, int, const std::string&) = 0;
    virtual Text* splitText(int) = 0;
};
}; // namespace dom

class Text_Impl : public virtual dom::Text, Node_Impl {
protected:
    Text_Impl(const std::string, dom::Document*);

public:
    friend class Document_Impl;

    virtual ~Text_Impl();

    virtual void serialize(std::fstream*, WhitespaceStrategy*);
    virtual const std::string& getName();
    virtual const std::string& getData();
    virtual const std::string& getValue();
    virtual void setData(const std::string&);
    virtual void setValue(const std::string&);
    virtual int getLength();
    virtual const std::string& substringData(int, int);
    virtual void appendData(const std::string&);
    virtual void insertData(int, const std::string&);
    virtual void deleteData(int, int);
    virtual void replaceData(int, int, const std::string&);
    virtual dom::Text* splitText(int);

    virtual Node* insertBefore(Node*, Node*) {
        return 0;
    }
    virtual Node* replaceChild(Node*, Node*) {
        return 0;
    }
    virtual Node* removeChild(Node*) {
        return 0;
    }
    virtual Node* appendChild(Node*) {
        return 0;
    }
};

#endif // TEXT_H
