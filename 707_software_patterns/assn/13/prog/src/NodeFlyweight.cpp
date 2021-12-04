#include "NodeFlyweight.hpp"

// declare the map
std::unordered_map<std::string, Flyweight*> FlyweightFactory::nodeFlyweights;

Flyweight* FlyweightFactory::getFlyweight(const std::string& name,
                                          const std::string& value,
                                          const short nodeType) {
    std::string key = name + value + std::to_string(nodeType);
    if (nodeFlyweights.find(key) == nodeFlyweights.end()) {
        nodeFlyweights[key] = new Flyweight(name, value, nodeType);
    }
    return nodeFlyweights[key];
}
