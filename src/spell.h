#ifndef SPELL_H
#define SPELL_H

#include "card.h"
#include "minion.h"
#include <string>
using namespace std;

class Spell: public Card {
    public:
        Spell(string name, string description, string type, int cost, int owner);

        string getName() const override;
        string getDesc() const override;
        string getType() const override;
        int getCost() const override;
};

class Banish: public Spell {
    public:
        Banish(int owner);
};
class Unsummon: public Spell {
    public:
        Unsummon(int owner);
};
class Recharge: public Spell {
    public:
        Recharge(int owner);
};
class Disenchant: public Spell {
    public:
        Disenchant(int owner);
};
class RaiseDead: public Spell {
    public:
        RaiseDead(int owner);
};
class Blizzard: public Spell {
    public:
        Blizzard(int owner);
};

#endif