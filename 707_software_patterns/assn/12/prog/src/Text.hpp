#ifndef TEXT_HPP
#define TEXT_HPP

#include "Node.hpp"
#include <string>

namespace dom {
class Document;

class Text : public virtual Node {
public:
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
    // virtual void serialize(std::fstream*, WhitespaceStrategy*) = 0;
};
}; // namespace dom

class Text_Impl : public virtual dom::Text, Node_Impl {
protected:
    Text_Impl(const std::string, dom::Document*);
    virtual ~Text_Impl();

public:
    friend class Document_Impl;

    virtual const std::string& getName() override;
    virtual const std::string& getData() override;
    virtual const std::string& getValue() override;
    virtual void setData(const std::string&) override;
    virtual void setValue(const std::string&) override;
    virtual int getLength() override;
    virtual const std::string& substringData(int, int) override;
    virtual void appendData(const std::string&) override;
    virtual void insertData(int, const std::string&) override;
    virtual void deleteData(int, int) override;
    virtual void replaceData(int, int, const std::string&) override;
    virtual dom::Text* splitText(int) override;
    // virtual void serialize(std::fstream*, WhitespaceStrategy*) override;
    virtual Node* insertBefore(Node*, Node*) override;
    virtual Node* replaceChild(Node*, Node*) override;
    virtual Node* removeChild(Node*) override;
    virtual Node* appendChild(Node*) override;

    virtual void accept(XMLVisitor*) override;
};

#endif // TEXT_HPP
