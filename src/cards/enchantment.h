#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include <string>

#include "card.h"
#include "minion.h"
using namespace std;

class Enchantment: public Minion {
   protected:
    shared_ptr<Minion> minion = nullptr;
    string atkDesc, defDesc;

   public:
    Enchantment(string name, string description, int cost, int owner, Game* game, int atk, int def, int actions, string atkDesc = "", string defDesc = "", string type = "Enchantment");
    virtual bool attach(int player, int target);
    virtual void activate() override;
    virtual void activate(int target) override;
    virtual void restoreAction() override;
    virtual void takeDamage(int dmg) override;
// might need a get base minion method() or just check if its an enchantment
// might need getActivatedAbility
    shared_ptr<Minion> getMinion() const;
    string getName() const override;
    string getDesc() const override;
    string getType() const override;
    int getCost() const override;

    int getAttack() const override;
    int getDefence() const override;
    int getActions() const override;
    string getAtkDesc() const;
    string getDefDesc() const;
};

class GiantStrength: public Enchantment {
    public:
     GiantStrength(int owner, Game* game);
};

class Enrage: public Enchantment {
    public:
     Enrage(int owner, Game* game);
     bool attach(int player, int target) override;
};

class Haste: public Enchantment {
    public:
     Haste(int owner, Game* game);
     void restoreAction();
};

class MagicFatigue: public Enchantment {
    public:
     MagicFatigue(int owner, Game* game);
     void activate() override;
     void activate(int target) override;
};

class Silence: public Enchantment {
    public:
     Silence(int owner, Game* game);
     void activate() override;
     void activate(int target) override;
};

#endif
