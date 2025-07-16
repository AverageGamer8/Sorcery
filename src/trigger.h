#ifndef TRIGGER_H
#define TRIGGER_H

#include <memory>
#include <vector>

#include "observer.h"

class Trigger {
  std::vector<shared_ptr<Observer>> observers;

public:
    void attach(Observer *obs);
    void detach(Observer *obs);
    void notify();
};

#endif