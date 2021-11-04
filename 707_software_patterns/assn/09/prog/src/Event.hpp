#include <string>
#include <vector>

class Event {
public:
    enum Type { TYPE1, TYPE2, TYPE3, NONE };

    static const std::vector<std::string> names;
    Event(Type type_, const std::string& message_)
        : type(type_), message(message_) {}

    Type type;
    // Other Event stuff...
    std::string message;
};
