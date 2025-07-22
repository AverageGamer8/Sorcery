#ifndef SPELL_H
#define SPELL_H

#include "card.h"
#include "minion.h"
#include "ritual.h"
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
        virtual void expend(shared_ptr<Minion> minion) = 0;
        virtual void expend(shared_ptr<Ritual> ritual) = 0;

        virtual ~Spell() = default;
};

class Banish: public Spell {
    public:
        Banish(int owner, shared_ptr<Game> game);
        void expend() override;
        void expend(shared_ptr<Minion> minion) override;
        void expend(shared_ptr<Ritual> ritual) override;
};
class Unsummon: public Spell {
    public:
        Unsummon(int owner, shared_ptr<Game> game);
        void expend() override;
        void expend(shared_ptr<Minion> minion) override;
        void expend(shared_ptr<Ritual> ritual) override;
};
class Recharge: public Spell {
    public:
        Recharge(int owner, shared_ptr<Game> game);
        void expend() override;
        void expend(shared_ptr<Minion> minion) override;
        void expend(shared_ptr<Ritual> ritual) override;
};
class Disenchant: public Spell {
    public:
        Disenchant(int owner, shared_ptr<Game> game);
        void expend() override;
        void expend(shared_ptr<Minion> minion) override;
        void expend(shared_ptr<Ritual> ritual) override;
};
class RaiseDead: public Spell {
    public:
        RaiseDead(int owner, shared_ptr<Game> game);
        void expend() override;
        void expend(shared_ptr<Minion> minion) override;
        void expend(shared_ptr<Ritual> ritual) override;
};
class Blizzard: public Spell {
    public:
        Blizzard(int owner, shared_ptr<Game> game);
        void expend() override;
        void expend(shared_ptr<Minion> minion) override;
        void expend(shared_ptr<Ritual> ritual) override;
};

#endif