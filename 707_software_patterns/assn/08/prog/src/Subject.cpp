#include "Subject.hpp"
#include "Observer.hpp"
#include <algorithm>

void Subject::attach(Observer* observer) {
    observers.push_back(observer);
}

void Subject::detach(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer),
                    observers.end());
}

bool Subject::notify(dom::Node* container, short targetType,
                     std::string& target) {
    bool result = true;

    for (std::vector<Observer*>::iterator i = observers.begin();
         i != observers.end(); i++) {
        result &= (*i)->update(container, targetType, target);
    }

    return result;
}
