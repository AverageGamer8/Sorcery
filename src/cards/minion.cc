#include "minion.h"

#include <iostream>  // todo remove debug
#include <memory>
#include <string>

#include "../gameModel/game.h"
#include "../gameModel/player.h"
#include "card.h"
using namespace std;

Minion::Minion(string name, string description, int cost, int owner, shared_ptr<Game> game, int atk, int defence, int actions, string type)
    : Card{name, description, type, cost, owner, game}, atk{atk}, defence{defence}, actions{actions} {}

void Minion::attack() {
    shared_ptr<Player> opp = game->getPlayer(game->getInactiveIndex());
    opp->setLife(opp->getLife() - atk);
    if (opp->getLife() <= 0) {
        opp->setLife(0);
        game->setWinner(game->getActiveIndex());
    }
}

void Minion::attack(int target) {
    game->battleMinion(atk, target);
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
AirElemental::AirElemental(int owner, shared_ptr<Game> game) : Minion{"Air Elemental", "", 0, owner, game, 1, 1, 0} {}
EarthElemental::EarthElemental(int owner, shared_ptr<Game> game) : Minion{"Earth Elemental", "", 3, owner, game, 4, 4, 0} {}
BoneGolem::BoneGolem(int owner, shared_ptr<Game> game) : Minion{"Bone Golem", "", 2, owner, game, 1, 3, 0} {}
FireElemental::FireElemental(int owner, shared_ptr<Game> game) : Minion{"Fire Elemental", "", 2, owner, game, 2, 2, 0} {}
PotionSeller::PotionSeller(int owner, shared_ptr<Game> game) : Minion{"Potion Seller", "", 2, owner, game, 1, 3, 0} {}
NovicePyromancer::NovicePyromancer(int owner, shared_ptr<Game> game) : Minion{"Novice Pyromancer", "", 1, owner, game, 0, 1, 0} {}
ApprenticeSummoner::ApprenticeSummoner(int owner, shared_ptr<Game> game) : Minion{"Apprentice Summoner", "", 1, owner, game, 1, 1, 0} {}
MasterSummoner::MasterSummoner(int owner, shared_ptr<Game> game) : Minion{"Master Summoner", "", 3, owner, game, 2, 3, 0} {}