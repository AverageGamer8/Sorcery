#ifndef RITUAL_H
#define RITUAL_H

#include "../trigger.h"  // TODO: needed? currently attaching observer here.
#include "../triggeredability.h"
#include "card.h"
using namespace std;

class Game;

class Ritual : public Card {
    shared_ptr<TriggeredAbility> triggerAbility;
    int activationCost;
    int charges;
    Trigger::TriggerType triggerType;

   public:
    Ritual(string name, string description, int cost, int owner, shared_ptr<Game> game,
           shared_ptr<TriggeredAbility> triggerAbility, int activationCost, int charges,
           Trigger::TriggerType triggerType, string type = "Ritual");

    int getActivationCost() const;
    int getCharges() const;
    void setCharges(int charges);

    void attachAbilities();
    void detachAbilities();
    
    string getName() const override;
    string getDesc() const override;
    string getType() const override;
    int getCost() const override;

    virtual ~Ritual() = default;
};

class DarkRitual : public Ritual {
   public:
    DarkRitual(int owner, shared_ptr<Game> game);
};
class AuraOfPower : public Ritual {
   public:
    AuraOfPower(int owner, shared_ptr<Game> game);
};
class Standstill : public Ritual {
   public:
    Standstill(int owner, shared_ptr<Game> game);
};

#endif
