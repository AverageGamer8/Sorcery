#ifndef SPELL_H
#define SPELL_H

#include "card.h"
#include "minion.h"
#include "ritual.h"
#include <string>
using namespace std;

class Spell: public Card {
    public:
        Spell(string name, string description, int cost, int owner, Game* game, string type = "Spell");

        string getName() const override;
        string getDesc() const override;
        string getType() const override;
        int getCost() const override;

        virtual bool expend() = 0; // might be better to just give integer targets
        virtual bool expend(int minion, int player) = 0; // ie int player, int minion
        virtual bool expend(int player) = 0; // int player

        virtual ~Spell() = default;
};

class Banish: public Spell {
    public:
        Banish(int owner, Game* game);
        bool expend() override;
        bool expend(int minion, int player) override;
        bool expend(int player) override;
};
class Unsummon: public Spell {
    public:
        Unsummon(int owner, Game* game);
        bool expend() override;
        bool expend(int minion, int player) override;
        bool expend(int player) override;
};
class Recharge: public Spell {
    public:
        Recharge(int owner, Game* game);
        bool expend() override;
        bool expend(int minion, int player) override;
        bool expend(int player) override;
};
class Disenchant: public Spell {
    public:
        Disenchant(int owner, Game* game);
        bool expend() override;
        bool expend(int minion, int player) override;
        bool expend(int player) override;
};
class RaiseDead: public Spell {
    public:
        RaiseDead(int owner, Game* game);
        bool expend() override;
        bool expend(int minion, int player) override;
        bool expend(int player) override;
};
class Blizzard: public Spell {
    public:
        Blizzard(int owner, Game* game);
        bool expend() override;
        bool expend(int minion, int player) override;
        bool expend(int player) override;
};

#endif