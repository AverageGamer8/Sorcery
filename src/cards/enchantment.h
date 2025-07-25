#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include <string>

#include "minion.h"
using namespace std;

class Enchantment : public Minion {
   protected:
    shared_ptr<Minion> minion = nullptr;
    string atkDesc, defDesc;

   public:
    Enchantment(string name, string description, int cost, int owner, Game* game, int atk, int def,
                int actions, shared_ptr<ActivatedAbility> activatedAbility, shared_ptr<TriggeredAbility> triggeredAbility,
                string atkDesc = "", string defDesc = "", string type = "Enchantment");

    virtual bool attach(int player, int target);
    virtual bool activate() override;
    virtual bool activate(int player, int target) override;
    virtual void restoreAction() override;
    bool takeDamage(int dmg) override;
    void increaseAtk(int amount) override;
    void increaseDef(int amount) override;
    shared_ptr<Minion> getMinion() const;
    void consumeAction() override;
    string getName() const override;
    string getDesc() const override;
    string getType() const override;
    int getCost() const override;
    string getEnchName() const;
    string getEnchDesc() const;
    int getEnchCost() const;

    int getAttack() const override;
    int getDefence() const override;
    int getActions() const override;
    string getAtkDesc() const;
    string getDefDesc() const;
    shared_ptr<ActivatedAbility> getActivatedAbility() const override;
    shared_ptr<TriggeredAbility> getTriggeredAbility() const override;
    virtual int getActivateCost() const override;
};

class GiantStrength : public Enchantment {
   public:
    GiantStrength(int owner, Game* game);
};

class Enrage : public Enchantment {
   public:
    Enrage(int owner, Game* game);
    bool attach(int player, int target) override;
};

class Haste : public Enchantment {
   public:
    Haste(int owner, Game* game);
    void restoreAction();
};

class MagicFatigue : public Enchantment {
   public:
    MagicFatigue(int owner, Game* game);
    int getActivateCost() const override;
};

class Silence : public Enchantment {
   public:
    Silence(int owner, Game* game);
    bool activate() override;
    bool activate(int player, int target) override;
};

#endif
