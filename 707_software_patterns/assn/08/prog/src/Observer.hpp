#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "Node.hpp"

#include <string>

class Subject;

class Observer {
protected:
    Observer() {}

public:
    virtual void update(Subject*) = 0;
};

#endif // OBSERVER_HPP
