#ifndef TRIGGER_H
#define TRIGGER_H

#include <memory>
#include <vector>

#include "observer.h"

class Trigger {
  std::vector<std::shared_ptr<Observer>> observers;

public:
  void attach(std::shared_ptr<Observer> obs);
  void detach(std::shared_ptr<Observer> obs);
  void notifyObservers();

  enum class TriggerType { TurnStart, TurnEnd, MinionEnter, MinionExit };
};

#endif