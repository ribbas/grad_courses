#include "Subject.hpp"
#include "Observer.hpp"
#include <algorithm>

Subject::Subject() {}

Subject::~Subject() {
    for (unsigned int i = 0; i < observers.size(); i++) {
        delete observers[i];
        observers[i] = nullptr;
    }
}

void Subject::attach(Observer* observer) {
    observers.push_back(observer);
}

void Subject::detach(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer),
                    observers.end());
}

void Subject::notify() {

    for (std::vector<Observer*>::iterator observerIter = observers.begin();
         observerIter != observers.end(); observerIter++) {
        (*observerIter)->update(this);
    }
}
