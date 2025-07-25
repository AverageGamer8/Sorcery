#ifndef SPELL_H
#define SPELL_H

#include <string>

#include "card.h"
#include "minion.h"
#include "ritual.h"
using namespace std;

class Spell : public Card {
   public:
    Spell(string name, string description, int cost, int owner, Game* game, string type = "Spell");

    string getName() const override;
    string getDesc() const override;
    string getType() const override;
    int getCost() const override;

    virtual bool expend() = 0;
    virtual bool expend(int player, int minion) = 0;
    virtual bool expend(int player) = 0;

    virtual ~Spell() = default;
};

class Banish : public Spell {
   public:
    Banish(int owner, Game* game);
    bool expend() override;
    bool expend(int player, int minion) override;
    bool expend(int player) override;
};
class Unsummon : public Spell {
   public:
    Unsummon(int owner, Game* game);
    bool expend() override;
    bool expend(int player, int minion) override;
    bool expend(int player) override;
};
class Recharge : public Spell {
   public:
    Recharge(int owner, Game* game);
    bool expend() override;
    bool expend(int player, int minion) override;
    bool expend(int player) override;
};
class Disenchant : public Spell {
   public:
    Disenchant(int owner, Game* game);
    bool expend() override;
    bool expend(int player, int minion) override;
    bool expend(int player) override;
};
class RaiseDead : public Spell {
   public:
    RaiseDead(int owner, Game* game);
    bool expend() override;
    bool expend(int player, int minion) override;
    bool expend(int player) override;
};
class Blizzard : public Spell {
   public:
    Blizzard(int owner, Game* game);
    bool expend() override;
    bool expend(int player, int minion) override;
    bool expend(int player) override;
};

#endif