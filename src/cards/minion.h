#ifndef MINION_H
#define MINION_H

#include <string>

#include "card.h"
using namespace std;

class Minion : public Card {
    int atk;
    int defence;
    int actions;

   public:
    Minion(string name, string description, int cost, int owner, int atk, int defence, int actions, string type = "Minion");
    void attack();
    void attack(int target);
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

    void setDefence(int defence);
};

class AirElemental : public Minion {
   public:
    AirElemental(int owner);
};
class EarthElemental : public Minion {
   public:
    EarthElemental(int owner);
};
class BoneGolem : public Minion {
   public:
    BoneGolem(int owner);
};
class FireElemental : public Minion {
   public:
    FireElemental(int owner);
};
class PotionSeller : public Minion {
   public:
    PotionSeller(int owner);
};
class NovicePyromancer : public Minion {
   public:
    NovicePyromancer(int owner);
};
class ApprenticeSummoner : public Minion {
   public:
    ApprenticeSummoner(int owner);
};
class MasterSummoner : public Minion {
   public:
    MasterSummoner(int owner);
};

#endif
