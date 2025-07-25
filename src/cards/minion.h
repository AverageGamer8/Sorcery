#ifndef MINION_H
#define MINION_H

#include <string>

#include "abilities/activatedability.h"
#include "abilities/triggeredability.h"
#include "card.h"

using namespace std;

class Minion : public Card, public enable_shared_from_this<Minion> {
   protected:
    int atk;
    int def;
    int actions;
    shared_ptr<ActivatedAbility> activatedAbility;
    shared_ptr<TriggeredAbility> triggeredAbility;

   public:
    Minion(string name, string description, int cost, int owner,
           Game* game, int atk, int def, int actions,
           shared_ptr<ActivatedAbility> activatedAbility, shared_ptr<TriggeredAbility> triggeredAbility,
           string type = "Minion");
    void attack();
    void attack(int target);
    virtual bool activate();
    virtual bool activate(int player, int minion);
    virtual void restoreAction();
    virtual void consumeAction();
    virtual bool takeDamage(int dmg);
    
    string getName() const override;
    string getDesc() const override;
    string getType() const override;
    int getCost() const override;

    virtual int getAttack() const;
    virtual int getDefence() const;
    virtual int getActions() const;
    virtual shared_ptr<ActivatedAbility> getActivatedAbility() const;
    virtual shared_ptr<TriggeredAbility> getTriggeredAbility() const;
    virtual int getActivateCost() const;

    void setDefence(int def);
    void setAttack(int atk);
    void setActions(int actions);
    virtual void increaseAtk(int amount);
    virtual void increaseDef(int amount);

    virtual ~Minion() = default;
};

class AirElemental : public Minion {
   public:
    AirElemental(int owner, Game* game);
};
class EarthElemental : public Minion {
   public:
    EarthElemental(int owner, Game* game);
};
class BoneGolem : public Minion {
   public:
    BoneGolem(int owner, Game* game);
};
class FireElemental : public Minion {
   public:
    FireElemental(int owner, Game* game);
};
class PotionSeller : public Minion {
   public:
    PotionSeller(int owner, Game* game);
};
class NovicePyromancer : public Minion {
   public:
    NovicePyromancer(int owner, Game* game);
};
class ApprenticeSummoner : public Minion {
   public:
    ApprenticeSummoner(int owner, Game* game);
};
class MasterSummoner : public Minion {
   public:
    MasterSummoner(int owner, Game* game);
};

#endif
