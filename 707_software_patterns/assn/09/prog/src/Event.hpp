#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

namespace dom {

struct Event {
    const std::string message;

    Event(const std::string& message_) : message(message_) {}
};

} // namespace dom

#endif // EVENT_HPP
