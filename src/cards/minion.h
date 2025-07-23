#ifndef MINION_H
#define MINION_H

#include <string>

#include "card.h"
#include "../activatedability.h"
#include "../triggeredability.h"

using namespace std;

class Minion : public Card {
   protected:
    int atk;
    int def;
    int actions;
    shared_ptr<ActivatedAbility> activatedAbility;
    shared_ptr<TriggeredAbility> triggeredAbility;

   public:
    Minion(string name, string description, int cost, int owner, 
        shared_ptr<Game> game, int atk, int def, int actions, 
        shared_ptr<ActivatedAbility> activatedAbility, shared_ptr<TriggeredAbility> triggeredAbility,
        string type = "Minion");
    void attack();
    // void attack(int target); // TODO: causes segfault, solution: pass in self. , std::enable_shared_from_this<Minion>
    void attack(int target, std::shared_ptr<Minion> self);
    virtual bool activate();
    virtual bool activate(int target);
    void attachAbilities();
    void detachAbilities();
    virtual void restoreAction();
    virtual void consumeAction();
    virtual void takeDamage(int dmg);

    string getName() const override;
    string getDesc() const override;
    string getType() const override;
    int getCost() const override;
    
    virtual int getAttack() const;
    virtual int getDefence() const;
    virtual int getActions() const;
    shared_ptr<ActivatedAbility> getActivatedAbility() const;
    shared_ptr<TriggeredAbility> getTriggeredAbility() const;

    void setDefence(int def);
    void setAttack(int atk);
    void setActions(int actions);

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
