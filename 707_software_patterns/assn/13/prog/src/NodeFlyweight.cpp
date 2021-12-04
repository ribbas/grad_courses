#include "NodeFlyweight.hpp"

#include <iostream>

size_t NodeFlyweight::Hash::operator()(NodeFlyweight* flyweight) const {
    std::string temp = flyweight->name + flyweight->value + "0";
    //    std::to_string(flyweight->nodeType);
    return std::hash<std::string>()(temp);
}

NodeFlyweight* NodeFlyweightFactory::getFlyweight(const std::string& name,
                                                  const std::string& value,
                                                  const short nodeType) {
    std::cout << "YO_" << name << '_' << value << '_' << nodeType << '\n';
    NodeFlyweight lookupFlyweight(name, value, nodeType);
    auto flyweightIt = nodeFlyweights.find(&lookupFlyweight);
    if (flyweightIt == nodeFlyweights.end()) {
        // std::cout << "not found\n";
        return *(nodeFlyweights.insert(new NodeFlyweight(name, value, nodeType))
                     .first);
    }
    std::cout << "found\n";
    return *flyweightIt;
}

// Declare the set
std::unordered_set<NodeFlyweight*, NodeFlyweight::Hash>
    NodeFlyweightFactory::nodeFlyweights;
