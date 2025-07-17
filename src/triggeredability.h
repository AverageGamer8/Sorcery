#ifndef TRIGGEREDABILITY_H
#define TRIGGEREDABILITY_H

#include "ability.h"
#include "observer.h"

class Game;

class TriggeredAbility : public Observer, public Ability {
   protected:
    Game *game;

   public:
    TriggeredAbility(Game *game) : game{game} {}

    virtual void activate() override = 0;
    void notify() override;
    virtual ~TriggeredAbility() = default;
};

#endif