#include "Flyweight.hpp"

// declare the map
std::unordered_map<std::string, dom::Flyweight*>
    dom::FlyweightFactory::nodeFlyweights;

dom::Flyweight::Flyweight(const std::string& _name, const std::string& _value,
                          const short _nodeType)
    : name(_name), value(_value), nodeType(_nodeType) {}

dom::Flyweight* dom::FlyweightFactory::getFlyweight(const std::string& name,
                                                    const std::string& value,
                                                    const short nodeType) {
    std::string key = name + value + std::to_string(nodeType);
    if (nodeFlyweights.find(key) == nodeFlyweights.end()) {
        nodeFlyweights[key] = new Flyweight(name, value, nodeType);
    }
    return nodeFlyweights[key];
}
