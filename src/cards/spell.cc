#include "spell.h"
#include "card.h"
#include "../gameModel/game.h"
#include <string>
using namespace std;

Spell::Spell(string name, string description, int cost, int owner, shared_ptr<Game> game, string type) : Card{name, description, type, cost, owner, game} {};

string Spell::getName() const {
    return name;
}

string Spell::getDesc() const {
    return description;
}

string Spell::getType() const {
    return type;
}

int Spell::getCost() const {
    return cost;
}

// Specific Spells
Banish::Banish(int owner, shared_ptr<Game> game) : Spell{"Banish", "Destroy target minion or ritual", 2, owner, game} {}
void Banish::expend() {
    // TODO: Handle exception
    return;
}

Unsummon::Unsummon(int owner, shared_ptr<Game> game) : Spell{"Unsummon", "Return target minion to its owner's hand", 1, owner, game} {}
void Unsummon::expend() {
    // TODO: Handle exception
    return;
}

Recharge::Recharge(int owner, shared_ptr<Game> game) : Spell{"Recharge", "Your ritual gains 3 charges", 1, owner, game} {}
void Recharge::expend() {
    // TODO: Handle exception
    return;
}

Disenchant::Disenchant(int owner, shared_ptr<Game> game) : Spell{"Disenchant", "Destroy the top enchantment on target minion", 1, owner, game} {}
void Disenchant::expend() {
    // TODO: Handle exception
    return;
}

RaiseDead::RaiseDead(int owner, shared_ptr<Game> game) : Spell{"RaiseDead", "Resurrect the top minion in your graveyard and set its defence to 1", 1, owner, game} {}
void RaiseDead::expend() {
    auto curr = game->getPlayer(game->getActiveIndex());
    if (curr->getBoard()->isFull()) {
        // TODO: Handle exception
        return;
    }
    if (curr->getGraveyard()->isEmpty()) {
        // TODO: Handle exception
        return;
    }

    auto m = curr->getGraveyard()->popTopMinion();
    m->setDefence(1);
    curr->getBoard()->addMinion(m);
}

Blizzard::Blizzard(int owner, shared_ptr<Game> game) : Spell{"Blizzard", "Deal 2 damage to all minions", 3, owner, game} {}
void Blizzard::expend() {
    auto curr = game->getPlayer(game->getActiveIndex());
    auto opp = game->getPlayer(game->getInactiveIndex());
    for (auto& minion : curr->getBoard()->getMinions()) {
        minion->setDefence(minion->getDefence() - 2);
    }
    for (auto& minion : opp->getBoard()->getMinions()) {
        minion->setDefence(minion->getDefence() - 2);
    }
}
