#ifndef RITUAL_H
#define RITUAL_H

#include "card.h"
#include "../triggeredability.h"
using namespace std;

class Ritual: public Card {
    shared_ptr<TriggeredAbility> triggerAbility;
    int activationCost;
    int charges;

    string getName() const override;
    string getDesc() const override;
    string getType() const override;
    int getCost() const override;

    public:
        Ritual(string name, string description, int cost, int owner, shared_ptr<Game> game, shared_ptr<TriggeredAbility> triggerAbility, int activationCost, int charges, string type = "Ritual");
        int getActivationCost() const;
        int getCharges() const;
        void setCharges(int charges);
};

class DarkRitual: public Ritual {
    public:
        DarkRitual(int owner, shared_ptr<Game> game);
};
class AuraOfPower: public Ritual {
    public:
        AuraOfPower(int owner, shared_ptr<Game>);
};
class Standstill: public Ritual {
    public:
        Standstill(int owner, shared_ptr<Game>);
};


#endif
