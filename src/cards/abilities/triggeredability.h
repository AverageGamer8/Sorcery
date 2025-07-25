#ifndef TRIGGEREDABILITY_H
#define TRIGGEREDABILITY_H

#include <memory>

#include "ability.h"
#include "observer.h"
#include "trigger.h"

using namespace std;

class Game;

class TriggeredAbility : public Observer, public Ability {
   protected:
    Game* game;
    int player;
    Trigger::TriggerType type;

   public:
    TriggeredAbility(Game* game, int player, const string& desc, Trigger::TriggerType type)
        : Ability(desc), game{game}, player{player}, type{type} {}

    Trigger::TriggerType getTriggerType() const;
    virtual bool activate() override = 0;
    void notify() override;
    virtual bool shouldTrigger() const = 0;
    virtual ~TriggeredAbility() = default;
};

class OnStartGainMagic : public TriggeredAbility {
   public:
    OnStartGainMagic(Game* game, int player);
    bool activate() override;
    bool shouldTrigger() const override;
};
class OnEnterBuff : public TriggeredAbility {
   public:
    OnEnterBuff(Game* game, int player);
    bool activate() override;
    bool shouldTrigger() const override;
};
class OnEnterDestroy : public TriggeredAbility {
   public:
    OnEnterDestroy(Game* game, int player);
    bool activate() override;
    bool shouldTrigger() const override;
};

class OnExitGainBuff : public TriggeredAbility {
   public:
    OnExitGainBuff(Game* game, int player);
    bool activate() override;
    bool shouldTrigger() const override;
};
class OnEnterDamage : public TriggeredAbility {
   public:
    OnEnterDamage(Game* game, int player);
    bool activate() override;
    bool shouldTrigger() const override;
};
class OnTurnEndBuff : public TriggeredAbility {
   public:
    OnTurnEndBuff(Game* game, int player);
    bool activate() override;
    bool shouldTrigger() const override;
};

#endif