#ifndef TRIGGER_H
#define TRIGGER_H

#include <memory>
#include <vector>

class Trigger {
   public:
    enum class TriggerType { TurnStart,
                             TurnEnd,
                             MinionEnter,
                             MinionExit };
};

#endif