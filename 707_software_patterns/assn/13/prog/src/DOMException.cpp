#include "DOMException.hpp"

dom::DOMException::DOMException(int r, const std::string& d)
    : reason(r), description(d) {}

dom::DOMException::~DOMException() {}

int dom::DOMException::getReason() {
    return reason;
}
const std::string& dom::DOMException::getDescription() {
    return description;
}
