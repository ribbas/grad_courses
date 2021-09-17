#include <fstream>
#include <ios>
#include <string>

#include "Node.hpp"

class DOMSerializerContext;

class XMLSerializerStrategy {

public:
    DOMSerializerContext* domSerializerContext;
    int indentationLevel;
    std::fstream file;
    std::string newline;

    XMLSerializerStrategy(const std::string&, const std::string&);
    virtual ~XMLSerializerStrategy() {}
    void serialize(dom::Node*);
    virtual void prettyIndentation() = 0;
    virtual void multipleAttr(int) = 0;
};

class XMLSerializerContext {

private:
    XMLSerializerStrategy* strategy_;

public:
    XMLSerializerContext(XMLSerializerStrategy* = nullptr);
    ~XMLSerializerContext();

    void serialize(dom::Node*);

    void setStrategy(XMLSerializerStrategy*);
};

class XMLSerializerPretty : public XMLSerializerStrategy {
private:
    void prettyIndentation() override;
    void multipleAttr(int) override;

public:
    XMLSerializerPretty(const std::string&);
};

class XMLSerializerMinimal : public XMLSerializerStrategy {
private:
    void prettyIndentation() override;
    void multipleAttr(int) override;

public:
    XMLSerializerMinimal(const std::string&);
};

class DOMSerializerStrategy {

public:
    DOMSerializerStrategy(dom::Node*) {}
    virtual ~DOMSerializerStrategy() {}
};

class DOMSerializerContext {
    /**
     * @var Strategy The DOMSerializerContext maintains a reference to one of
     * the Strategy objects. The DOMSerializerContext does not know the concrete
     * class of a strategy. It should work with all strategies via the Strategy
     * interface.
     */
private:
    DOMSerializerStrategy* strategy_;

public:
    DOMSerializerContext(DOMSerializerStrategy* = nullptr);
    ~DOMSerializerContext();

    void findNodeType(dom::Node*, XMLSerializerStrategy*);

    void setStrategy(DOMSerializerStrategy*);
};

class DocumentSerializer : public DOMSerializerStrategy {
public:
    DocumentSerializer(dom::Node*, XMLSerializerStrategy*);
};

class ElementSerializer : public DOMSerializerStrategy {
public:
    ElementSerializer(dom::Node*, XMLSerializerStrategy*);
};

class AttrSerializer : public DOMSerializerStrategy {
public:
    AttrSerializer(dom::Node*, XMLSerializerStrategy*);
};

class TextSerializer : public DOMSerializerStrategy {
public:
    TextSerializer(dom::Node*, XMLSerializerStrategy*);
};
