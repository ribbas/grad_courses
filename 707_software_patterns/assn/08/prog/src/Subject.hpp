#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include "Node.hpp"
#include <string>
#include <vector>

class Observer;

class Subject {
private:
    std::vector<Observer*> observers;

protected:
    Subject();

public:
    virtual void attach(Observer*);
    virtual void detach(Observer*);

protected:
    void notify();
};

#endif // SUBJECT_HPP
