#ifndef MINION_H
#define MINION_H

#include <string>

#include "card.h"
using namespace std;

class Minion : public Card {
   protected:
    int atk;
    int defence;
    int actions;

   public:
    Minion(string name, string description, int cost, int owner, shared_ptr<Game> game, int atk, int defence, int actions, string type = "Minion");
    void attack();
    // void attack(int target); // TODO: causes segfault, solution: pass in self. , std::enable_shared_from_this<Minion>
    void attack(int target, std::shared_ptr<Minion> self);
    void activate();
    void activate(int target);
    void restoreAction();
    void getHit();

    string getName() const override;
    string getDesc() const override;
    string getType() const override;
    int getCost() const override;
    
    int getAttack() const;
    int getDefence() const;
    int getActions() const;

    void setDefence(int defence);
    void setActions(int actions);

    virtual ~Minion() = default;
};

class AirElemental : public Minion {
   public:
    AirElemental(int owner, shared_ptr<Game> game);
};
class EarthElemental : public Minion {
   public:
    EarthElemental(int owner, shared_ptr<Game> game);
};
class BoneGolem : public Minion {
   public:
    BoneGolem(int owner, shared_ptr<Game> game);
};
class FireElemental : public Minion {
   public:
    FireElemental(int owner, shared_ptr<Game> game);
};
class PotionSeller : public Minion {
   public:
    PotionSeller(int owner, shared_ptr<Game> game);
};
class NovicePyromancer : public Minion {
   public:
    NovicePyromancer(int owner, shared_ptr<Game> game);
};
class ApprenticeSummoner : public Minion {
   public:
    ApprenticeSummoner(int owner, shared_ptr<Game> game);
};
class MasterSummoner : public Minion {
   public:
    MasterSummoner(int owner, shared_ptr<Game> game);
};

#endif
