#ifndef DOM_FLYWEIGHT_HPP
#define DOM_FLYWEIGHT_HPP

#include <string>
#include <unordered_map>

namespace dom {

struct Flyweight {
    std::string name;
    std::string value;
    short nodeType;

    Flyweight(const std::string&, const std::string&, const short);
};

// Factory that stores shared flyweight nodes
class FlyweightFactory {
public:
    static Flyweight* getFlyweight(const std::string&, const std::string&,
                                   const short);

private:
    // map of flyweight pointers
    static std::unordered_map<std::string, Flyweight*> nodeFlyweights;
};
} // namespace dom

#endif // DOM_FLYWEIGHT_HPP