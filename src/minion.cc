#include "minion.h"
#include "game.h"
#include "player.h"
#include "card.h"
#include <memory>
#include <string>
using namespace std;

Minion::Minion(string name, string description, string type, int cost, int owner, int atk, int defence, int actions) : Card{name, description, type, cost, owner}, atk{atk}, defence{defence}, actions{actions} {}

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

void expend() {
    // TODO
    return;
}

// Specific Minions
AirElemental::AirElemental(int owner) : Minion{"Air Elemental", "", "Minion", 0, owner, 1, 1, 0} {}
EarthElemental::EarthElemental(int owner) : Minion{"Earth Elemental", "", "Minion", 3, owner, 4, 4, 0} {}
BoneGolem::BoneGolem(int owner) : Minion{"Bone Golem", "", "Minion", 2, owner, 1, 3, 0} {}
FireElemental::FireElemental(int owner) : Minion{"Fire Elemental", "", "Minion", 2, owner, 2, 2, 0} {}
PotionSeller::PotionSeller(int owner) : Minion{"Potion Seller", "", "Minion", 2, owner, 1, 3, 0} {}
NovicePyromancer::NovicePyromancer(int owner) : Minion{"Novice Pyromancer", "", "Minion", 1, owner, 0, 1, 0} {}
ApprenticeSummoner::ApprenticeSummoner(int owner) : Minion{"Apprentice Summoner", "", "Minion", 1, owner, 1, 1, 0} {}
MasterSummoner::MasterSummoner(int owner) : Minion{"Master Summoner", "", "Minion", 3, owner, 2, 3, 0} {}