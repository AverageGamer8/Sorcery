#include "minion.h"

#include <memory>
#include <string>

#include "../gameModel/game.h"
#include "../gameModel/player.h"
#include "card.h"
using namespace std;

Minion::Minion(string name, string description, int cost, int owner, int atk, int defence, int actions, string type) : Card{name, description, type, cost, owner}, atk{atk}, defence{defence}, actions{actions} {}

void Minion::attack() {
    Game* g = game.get();
    Player* opp = g->getPlayer(g->getInactiveIndex());

    opp->life -= atk;
}

void Minion::attack(int target) {
    Game* g = game.get();
    Player* opp = g->getPlayer(g->getInactiveIndex());

    opp->minions[target - 1].get()->defence -= atk;
    defence -= opp->minions[target - 1].get()->atk;
}

void Minion::setDefence(int defence) {
    this->defence = defence;
}

string Minion::getName() const {
    return name;
}

string Minion::getDesc() const {
    return description;
}

string Minion::getType() const {
    return type;
}

int Minion::getCost() const {
    return cost;
}
int Minion::getAttack() const {
    return atk;
}
int Minion::getDefence() const {
    return defence;
}

// Specific Minions
AirElemental::AirElemental(int owner) : Minion{"Air Elemental", "", 0, owner, 1, 1, 0} {}
EarthElemental::EarthElemental(int owner) : Minion{"Earth Elemental", "", 3, owner, 4, 4, 0} {}
BoneGolem::BoneGolem(int owner) : Minion{"Bone Golem", "", 2, owner, 1, 3, 0} {}
FireElemental::FireElemental(int owner) : Minion{"Fire Elemental", "", 2, owner, 2, 2, 0} {}
PotionSeller::PotionSeller(int owner) : Minion{"Potion Seller", "", 2, owner, 1, 3, 0} {}
NovicePyromancer::NovicePyromancer(int owner) : Minion{"Novice Pyromancer", "", 1, owner, 0, 1, 0} {}
ApprenticeSummoner::ApprenticeSummoner(int owner) : Minion{"Apprentice Summoner", "", 1, owner, 1, 1, 0} {}
MasterSummoner::MasterSummoner(int owner) : Minion{"Master Summoner", "", 3, owner, 2, 3, 0} {}