#ifndef TRIGGEREDABILITY_H
#define TRIGGEREDABILITY_H

#include "ability.h"
#include "observer.h"
#include <memory>

class Game;

class TriggeredAbility : public Observer, public Ability {
   protected:
    Game* game;
    int player;

   public:
    TriggeredAbility(Game* game, int player) : game{game}, player{player} {}

    virtual void activate() override = 0;
    void notify() override;
    virtual bool shouldTrigger() const = 0;
    virtual ~TriggeredAbility() = default;
};

class OnStartGainMagic: public TriggeredAbility {
    public:
        OnStartGainMagic(Game* game, int player);
        void activate() override;
        bool shouldTrigger() const override;
};
class OnEnterBuff: public TriggeredAbility {
    public:
        OnEnterBuff(Game* game, int player);
        void activate() override;
        bool shouldTrigger() const override;
};
class OnEnterDestroy: public TriggeredAbility {
    public:
        OnEnterDestroy(Game* game, int player);
        void activate() override;
        bool shouldTrigger() const override;
};

#endif