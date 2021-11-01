#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <vector>

class Observer;

class Subject {
private:
    std::vector<Observer*> observers;

protected:
    Subject();

protected:
    void notify();

public:
    virtual ~Subject();
    virtual void attach(Observer*);
    virtual void detach(Observer*);
};

#endif // SUBJECT_HPP
