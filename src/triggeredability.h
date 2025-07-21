#ifndef TRIGGEREDABILITY_H
#define TRIGGEREDABILITY_H

#include "ability.h"
#include "observer.h"
#include <memory>

class Game;

class TriggeredAbility : public Observer, public Ability {
   protected:
    std::shared_ptr<Game> game;

   public:
    TriggeredAbility(std::shared_ptr<Game> game) : game{game} {}

    virtual void activate() override = 0;
    void notify() override;
    virtual ~TriggeredAbility() = default;
};

class OnStartGainMagic: public TriggeredAbility {
    public:
        OnStartGainMagic(std::shared_ptr<Game> game);
        void activate() override;
};
class OnEnterBuff: public TriggeredAbility {
    public:
        OnEnterBuff(std::shared_ptr<Game> game);
        void activate() override;
};
class OnEnterDestroy: public TriggeredAbility {
    public:
        OnEnterDestroy(std::shared_ptr<Game> game);
        void activate() override;
};

#endif