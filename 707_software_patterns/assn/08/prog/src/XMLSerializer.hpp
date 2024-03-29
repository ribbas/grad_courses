#ifndef XML_SERIALIZER_HPP
#define XML_SERIALIZER_HPP

#include "Node.hpp"
#include <fstream>
#include <ios>
#include <string>

//
// XMLSerializer is Serialization Strategy Context
// Node is Serialization Strategy and output stream Strategy Context
// Document, Element, Attr, Text are Serialization Concrete Strategies
// java.io.Writer is output stream Strategy
// java.io.BufferedWriter is output stream Concrete Strategy
//
class XMLSerializer {
private:
    std::fstream* file;

public:
    XMLSerializer(std::fstream*);
    ~XMLSerializer();

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

public:
    //
    // Strategized serialization
    //
    virtual void serializePretty(dom::Node*);
    virtual void serializeMinimal(dom::Node*);
};

#endif // XML_SERIALIZER_HPP
