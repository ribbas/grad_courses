#ifndef DOM_FLYWEIGHT_HPP
#define DOM_FLYWEIGHT_HPP

#include <sstream>
#include <string>
#include <unordered_map>

namespace dom {

class Document;

struct Flyweight {
    std::string name;
    std::string value;
    short nodeType;
    dom::Document* document;

    Flyweight(const std::string&, const std::string&, const short,
              dom::Document*);
};

// Factory that stores shared flyweight nodes
class FlyweightFactory {
public:
    static Flyweight* getFlyweight(const std::string&, const std::string&,
                                   const short, dom::Document*);

private:
    // map of flyweight pointers
    static std::unordered_map<std::string, Flyweight*> nodeFlyweights;
};
} // namespace dom

#endif // DOM_FLYWEIGHT_HPP
