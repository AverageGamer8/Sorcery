#ifndef RITUAL_H
#define RITUAL_H

#include "abilities/trigger.h"  // TODO: needed? currently attaching observer here.
#include "abilities/triggeredability.h"
#include "card.h"
using namespace std;

class Game;

class Ritual : public Card {
    shared_ptr<TriggeredAbility> triggerAbility;
    int activationCost;
    int charges;

   public:
    Ritual(string name, string description, int cost, int owner, Game* game,
           shared_ptr<TriggeredAbility> triggerAbility, int activationCost, int charges, string type = "Ritual");

    int getActivationCost() const;
    int getCharges() const;
    void setCharges(int charges);
    shared_ptr<TriggeredAbility> getTriggeredAbility() const;
    
    string getName() const override;
    string getDesc() const override;
    string getType() const override;
    int getCost() const override;

    virtual ~Ritual() = default;
};

class DarkRitual : public Ritual {
   public:
    DarkRitual(int owner, Game* game);
};
class AuraOfPower : public Ritual {
   public:
    AuraOfPower(int owner, Game* game);
};
class Standstill : public Ritual {
   public:
    Standstill(int owner, Game* game);
};

#endif
