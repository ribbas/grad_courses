#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include "Node.hpp"
#include <string>
#include <vector>

// namespace dom {
// class Node;
// };

class Observer;

class Subject {
private:
    std::vector<Observer*> observers;

public:
    void attach(Observer*);
    void detach(Observer*);

protected:
    bool notify(dom::Node*, short, std::string&);
};

#endif // SUBJECT_HPP
