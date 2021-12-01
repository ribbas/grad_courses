#ifndef XML_SERIALIZER_HPP
#define XML_SERIALIZER_HPP

#include "Node.hpp"
#include "XMLVisitor.hpp"

class XMLSerializer : public XMLVisitor {
private:
    std::fstream* file;
    WhitespaceStrategy* whitespace;

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

    virtual void visitDocument(dom::Document*) override;
    virtual void visitElement(dom::Element*) override;
    virtual void visitAttr(dom::Attr*) override;
    virtual void visitText(dom::Text*) override;

public:
    XMLSerializer(std::fstream*);
    ~XMLSerializer();
    virtual void serializePretty();
    virtual void serializeMinimal();
};

#endif // XML_SERIALIZER_HPP
