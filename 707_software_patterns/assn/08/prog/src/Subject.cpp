#include "Subject.hpp"
#include "Observer.hpp"
#include <algorithm>

Subject::Subject() {}

void Subject::attach(Observer* observer) {
    observers.push_back(observer);
}

void Subject::detach(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer),
                    observers.end());
}

void Subject::notify() {

    for (Observer* observer : observers) {
        observer->update(this);
    }
}
