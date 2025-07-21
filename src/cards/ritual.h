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
        Ritual(string name, string description, int cost, int owner, shared_ptr<TriggeredAbility> triggerAbility, int activationCost, int charges, string type = "Ritual");
        int getCharges();
        void setCharges(int charges);
};

class DarkRitual: public Ritual {
    public:
        DarkRitual(int owner);
};
class AuraOfPower: public Ritual {
    public:
        AuraOfPower(int owner);
};
class Standstill: public Ritual {
    public:
        Standstill(int owner);
};


#endif
