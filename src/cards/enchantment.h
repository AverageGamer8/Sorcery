#ifndef ENCHANTMENT_H
#define ENCHANTMENT_H

#include <string>

#include "card.h"
using namespace std;

class Enchantment: public Minion {
    shared_ptr<Minion> minion = nullptr;
    string atkDesc, defDesc;

   public:
    Enchantment(string name, string description, int cost, int owner, int atk, int def, int actions, string atkDesc = "", string defDesc = "");
    virtual void attach(shared_ptr<Minion> target) override;
    virtual void attack() override;
    virtual void attack(int target) override;
    virtual void activate() override;
    virtual void activate(int target) override;
    virtual void restoreAction() override;
    virtual void getHit(int dmg) override;
    
    shared_ptr<Minion> getMinion() const;
    string getName() const override;
    string getDesc() const override;
    string getType() const override;
    int getCost() const override;

    int getAttack() const;
    int getDefence() const;
    string& getAtkDesc() const;
    string& getDefDesc() const;
};

class GiantStrength: public Enchantment {
    public:
     GiantStrength(int owner);
};

class Enrage: public Enchantment {
    public:
     Enrage(int owner);
     Enrage::attach(shared_ptr<Minion> target) override;
};

class Haste: public Enchantment {
    public:
     Haste(int owner);
     void restoreAction();
};

class MagicFatigue: public Enchantment {
    public:
     MagicFatigue(int owner);
     void activate() override;
     void activate(int target) override;
};

class Silence: public Enchantment {
    public:
     Silence(int owner);
     void activate() override;
     void activate(int target) override;
};

#endif
