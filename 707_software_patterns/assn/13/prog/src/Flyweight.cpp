#include "Flyweight.hpp"

// declare the map
std::unordered_map<std::string, dom::Flyweight*>
    dom::FlyweightFactory::nodeFlyweights;

dom::Flyweight::Flyweight(const std::string& _name, const std::string& _value,
                          const short _nodeType, dom::Document* _document)
    : name(_name), value(_value), nodeType(_nodeType), document(_document) {}

dom::Flyweight* dom::FlyweightFactory::getFlyweight(const std::string& name,
                                                    const std::string& value,
                                                    const short nodeType,
                                                    dom::Document* document) {
    std::stringstream keySS;
    keySS << name << value << nodeType << document;
    std::string key = keySS.str();

    if (nodeFlyweights.find(key) == nodeFlyweights.end()) {
        nodeFlyweights[key] = new Flyweight(name, value, nodeType, document);
    }
    return nodeFlyweights[key];
}
