#include <fstream>
#include <ios>
#include <string>

#include "Node.hpp"

class XMLSerializerStrategy {
protected:
    int indentationLevel;
    std::fstream file;
    std::string newline;
    virtual void prettyIndentation() = 0;
    virtual void multipleAttr() = 0;

public:
    XMLSerializerStrategy(const std::string&, const std::string&);
    virtual ~XMLSerializerStrategy() {}
    void serialize(dom::Node*);
};

class XMLSerializerContext {
    /**
     * @var Strategy The XMLSerializerContext maintains a reference to one of
     * the Strategy objects. The XMLSerializerContext does not know the concrete
     * class of a strategy. It should work with all strategies via the Strategy
     * interface.
     */
private:
    XMLSerializerStrategy* strategy_;

public:
    XMLSerializerContext(XMLSerializerStrategy* = nullptr);
    ~XMLSerializerContext();

    void serialize(dom::Node*);

    /**
     * Usually, the XMLSerializerContext allows replacing a Strategy object at
     * runtime.
     */
    void set_strategy(XMLSerializerStrategy*);
};

class XMLSerializerPretty : public XMLSerializerStrategy {
private:
    void prettyIndentation() override;
    void multipleAttr() override;

public:
    XMLSerializerPretty(const std::string&);
};

class XMLSerializerMinimal : public XMLSerializerStrategy {
private:
    void prettyIndentation() override;
    void multipleAttr() override;

public:
    XMLSerializerMinimal(const std::string&);
};
