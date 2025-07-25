#ifndef ACTIVATEDABILITY_H
#define ACTIVATEDABILITY_H

#include <memory>

#include "ability.h"

using namespace std;

class Game;

class ActivatedAbility : public Ability {
   protected:
    Game* game;
    int cost;

   public:
    virtual bool activate() override = 0;
    virtual bool activate(int player, int minion) = 0;

    ActivatedAbility(Game* game, const string desc, int cost)
        : Ability(desc), game{game}, cost{cost} {}
    int getCost() const;

    virtual ~ActivatedAbility() = default;
};

class DealDamage : public ActivatedAbility {
   public:
    DealDamage(Game* game);
    bool activate() override;
    bool activate(int player, int minion) override;
};

class SummonAirElemental : public ActivatedAbility {
   public:
    SummonAirElemental(Game* game);
    bool activate() override;
    bool activate(int player, int minion) override;
};

class SummonThreeAirElemental : public ActivatedAbility {
   public:
    SummonThreeAirElemental(Game* game);
    bool activate() override;
    bool activate(int player, int minion) override;
};

#endif
