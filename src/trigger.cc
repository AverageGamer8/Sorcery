#include "trigger.h"

void Trigger::attach(std::shared_ptr<Observer> obs) {
    observers.emplace_back(obs);
}
void Trigger::detach(std::shared_ptr<Observer> obs) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == obs) {
            observers.erase(it);
            break;
        }
    }
}
void Trigger::notifyObservers() {
    for (auto &ob : observers) {
        ob->notify();
    }
}