#ifndef NODEFLYWEIGHT_HPP
#define NODEFLYWEIGHT_HPP

#include <unordered_map>

struct Flyweight {
public:
    std::string name;
    std::string value;
    short nodeType;

    Flyweight(const std::string& _name, const std::string& _value,
              const short _nodeType)
        : name(_name), value(_value), nodeType(_nodeType) {}
};

// Factory that stores shared flyweight nodes
class FlyweightFactory {
public:
    static Flyweight* getFlyweight(const std::string&, const std::string&,
                                   const short);

private:
    // Set of flyweight pointers
    static std::unordered_map<std::string, Flyweight*> nodeFlyweights;
};

#endif // NODEFLYWEIGHT_HPP
