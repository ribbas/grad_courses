#ifndef NODEFLYWEIGHT_HPP
#define NODEFLYWEIGHT_HPP

#include <sstream>
#include <unordered_map>
#include <unordered_set>

// Plain old data class for intrinsic data of node, to allow it to be shared,
//  a la flyweight pattern
struct NodeFlyweight {
public:
    std::string name;
    std::string value;
    short nodeType;

    NodeFlyweight(const std::string& _name, const std::string& _value,
                  const short _nodeType)
        : name(_name), value(_value), nodeType(_nodeType) {}

    struct Hash {
        size_t operator()(NodeFlyweight*) const;
    };
};

// Factory that stores shared flyweight nodes
class NodeFlyweightFactory {
public:
    static NodeFlyweight* getFlyweight(const std::string&, const std::string&,
                                       const short);

    // std::string getKey(const Node& ss) const {
    //     return ss.brand_ + "_" + ss.model_ + "_" + ss.color_;
    // }

private:
    // Set of flyweight pointers
    static std::unordered_set<NodeFlyweight*, NodeFlyweight::Hash>
        nodeFlyweights;
    // std::unordered_map<std::string, NodeFlyweight> flyweights_;
};

#endif // NODEFLYWEIGHT_HPP
