#include <fstream>
#include <ios>
#include <string>

#include "Node.hpp"

class XMLSerializerStrategy {
protected:
    int indentationLevel;
    std::fstream file;
    virtual void prettyIndentation();

public:
    XMLSerializerStrategy(const std::string& filename)
        : indentationLevel(0), file(filename.c_str(), std::ios_base::out) {}
    virtual ~XMLSerializerStrategy() {}
    virtual void serialize(dom::Node*) = 0;
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
    XMLSerializerContext(XMLSerializerStrategy* strategy = nullptr)
        : strategy_(strategy) {}
    ~XMLSerializerContext() {
        delete this->strategy_;
    }

    void serialize(dom::Node* node) {
        this->strategy_->serialize(node);
    }

    /**
     * Usually, the XMLSerializerContext allows replacing a Strategy object at
     * runtime.
     */
    void set_strategy(XMLSerializerStrategy* strategy) {
        delete this->strategy_;
        this->strategy_ = strategy;
    }
};

class XMLSerializerMinimal : public XMLSerializerStrategy {
public:
    XMLSerializerMinimal(const std::string& filename)
        : XMLSerializerStrategy(filename) {}
    void serialize(dom::Node*) override;
};

class XMLSerializerPretty : public XMLSerializerStrategy {
public:
    XMLSerializerPretty(const std::string& filename)
        : XMLSerializerStrategy(filename) {}
    void serialize(dom::Node*) override;
};
