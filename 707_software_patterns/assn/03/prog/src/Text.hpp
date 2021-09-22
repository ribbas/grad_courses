#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "DocumentNode.hpp"

namespace dom {
class Document;

class Text : public virtual DocumentNode {
public:
    virtual ~Text() {}

    virtual int getLength() = 0;
    virtual const std::string& substringData(int, int) = 0;
    virtual void appendData(const std::string&) = 0;
    virtual void insertData(int, const std::string&) = 0;
    virtual void deleteData(int, int) = 0;
    virtual void replaceData(int, int, const std::string&) = 0;
    virtual Text* splitText(int) = 0;
};
}; // namespace dom

class Text_Impl : public virtual dom::Text, DocumentNode_Impl {
protected:
    Text_Impl(const std::string value, dom::Document* document);

public:
    friend class Document_Impl;

    virtual ~Text_Impl();

    virtual int getLength();
    virtual const std::string& substringData(int, int);
    virtual void appendData(const std::string&);
    virtual void insertData(int, const std::string&);
    virtual void deleteData(int, int);
    virtual void replaceData(int, int, const std::string&);
    virtual dom::Text* splitText(int);
};

#endif // TEXT_H
