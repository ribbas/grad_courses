#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "Node.hpp"
#include <string>

// namespace dom {
// class Node;
// };

class Observer {
public:
    virtual bool update(dom::Node*, short, std::string&) = 0;
};

#endif // OBSERVER_HPP
