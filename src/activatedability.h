#ifndef ACTIVATEDABILITY_H
#define ACTIVATEDABILITY_H

#include <memory>

#include "ability.h"

using namespace std;

class Game;

class ActivatedAbility : public Ability {
   protected:
    shared_ptr<Game> game;
    int cost;

   public:
    virtual bool activate() override = 0;
    virtual bool activate(int target) = 0;

    ActivatedAbility(shared_ptr<Game> game, const string desc, int cost) 
        : Ability(desc), game{game}, cost{cost} {}
    int getCost() const;

    virtual ~ActivatedAbility() = default;
};

class DealDamage : public ActivatedAbility {
   public:
    DealDamage(shared_ptr<Game> game);
    bool activate() override;
    bool activate(int target) override;
};

class SummonAirElemental : public ActivatedAbility {
   public:
    SummonAirElemental(shared_ptr<Game> game);
    bool activate() override;
    bool activate(int target) override;
};

class SummonThreeAirElemental : public ActivatedAbility {
   public:
    SummonThreeAirElemental(shared_ptr<Game> game);
    bool activate() override;
    bool activate(int target) override;
};

#endif