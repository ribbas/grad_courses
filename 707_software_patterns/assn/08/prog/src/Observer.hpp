#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "Node.hpp"

class Subject;

class Observer {
protected:
    Observer();

public:
    virtual ~Observer();
    virtual void update(Subject*) = 0;
};

#endif // OBSERVER_HPP
