#ifndef XML_SERIALIZER_HPP
#define XML_SERIALIZER_HPP

#include "Node.hpp"
#include "XMLVisitor.hpp"
#include <fstream>
#include <ios>
#include <string>

class XMLSerializer : public XMLVisitor {
private:
    std::fstream* file;
    WhitespaceStrategy* whitespace;

public:
    XMLSerializer(std::fstream*);
    ~XMLSerializer();
    virtual void serializePretty();
    virtual void serializeMinimal();

private:
    class PrettyWhitespaceStrategy : public WhitespaceStrategy {
    private:
        int indentationLevel;

    public:
        PrettyWhitespaceStrategy();

        virtual void prettyIndentation(std::fstream*) override;
        virtual void incrementIndentation() override;
        virtual void decrementIndentation() override;
        virtual void newLine(std::fstream*) override;
    };

    class MinimalWhitespaceStrategy : public WhitespaceStrategy {
    public:
        virtual void prettyIndentation(std::fstream*) override;
        virtual void incrementIndentation() override;
        virtual void decrementIndentation() override;
        virtual void newLine(std::fstream*) override;
    };
    virtual void visitDocument(dom::Document* document);
    virtual void visitElement(dom::Element* element);
    virtual void visitAttr(dom::Attr* attr);
    virtual void visitText(dom::Text* text);
};

#endif // XML_SERIALIZER_HPP
