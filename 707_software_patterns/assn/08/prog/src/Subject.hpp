#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <vector>

class Observer;

class Subject {
private:
    std::vector<Observer*> observers;

protected:
    Subject();

public:
    virtual ~Subject();
    virtual void attach(Observer*);
    virtual void detach(Observer*);

protected:
    void notify();
};

#endif // SUBJECT_HPP
