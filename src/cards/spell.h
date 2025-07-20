#ifndef SPELL_H
#define SPELL_H

#include "card.h"
#include "minion.h"
#include <string>
using namespace std;

class Spell: public Card {
    public:
        Spell(string name, string description, int cost, int owner, shared_ptr<Game> game, string type = "Spell");

        string getName() const override;
        string getDesc() const override;
        string getType() const override;
        int getCost() const override;

        virtual void expend() = 0;
};

class Banish: public Spell {
    public:
        Banish(int owner, shared_ptr<Game> game);
        void expend() override;
};
class Unsummon: public Spell {
    public:
        Unsummon(int owner, shared_ptr<Game> game);
        void expend() override;
};
class Recharge: public Spell {
    public:
        Recharge(int owner, shared_ptr<Game> game);
        void expend() override;
};
class Disenchant: public Spell {
    public:
        Disenchant(int owner, shared_ptr<Game> game);
        void expend() override;
};
class RaiseDead: public Spell {
    public:
        RaiseDead(int owner, shared_ptr<Game> game);
        void expend() override;
};
class Blizzard: public Spell {
    public:
        Blizzard(int owner, shared_ptr<Game> game);
        void expend() override;
};

#endif