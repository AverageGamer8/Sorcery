#include "spell.h"
#include "card.h"
#include "../gameModel/game.h"
#include <string>
using namespace std;

Spell::Spell(string name, string description, int cost, int owner, string type) : Card{name, description, type, cost, owner} {};

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
Banish::Banish(int owner) : Spell{"Banish", "Destroy target minion or ritual", 2, owner} {}
void Banish::expend() {
    // TODO: Handle exception
    return;
}
void Banish::expend(shared_ptr<Minion> minion) {
    minion->setDefence(0);
}
void Banish::expend(shared_ptr<Ritual> ritual) {
    game->getPlayer(game->getActiveIndex())->getBoard()->setRitual(nullptr);
}

Unsummon::Unsummon(int owner) : Spell{"Unsummon", "Return target minion to its owner's hand", 1, owner} {}
void Unsummon::expend() {
    // TODO: Handle exception
    return;
}
void Unsummon::expend(shared_ptr<Minion> minion) {
    auto curr = game->getPlayer(game->getActiveIndex());
    if (curr->getHand()->isFull()) {
        // TODO: Handle exception
        return;
    }

    curr->getHand()->addCard(minion);
}
void Unsummon::expend(shared_ptr<Ritual> ritual) {
    // TODO: Handle exception
    return;
}

Recharge::Recharge(int owner) : Spell{"Recharge", "Your ritual gains 3 charges", 1, owner} {}
void Recharge::expend() {
    // TODO: Handle exception
    return;
}
void Recharge::expend(shared_ptr<Minion> minion) {
    // TODO: Handle exception
    return;
}
void Recharge::expend(shared_ptr<Ritual> ritual) {
    ritual->setCharges(ritual->getCharges() + 3);
}

Disenchant::Disenchant(int owner) : Spell{"Disenchant", "Destroy the top enchantment on target minion", 1, owner} {}
void Disenchant::expend() {
    // TODO: Handle exception
    return;
}
void Disenchant::expend(shared_ptr<Minion> minion) {
    // TODO: Destroy top enchantment on minion
    return;
}
void Disenchant::expend(shared_ptr<Ritual> ritual) {
    // TODO: Handle exception
    return;
}


RaiseDead::RaiseDead(int owner) : Spell{"RaiseDead", "Resurrect the top minion in your graveyard and set its defence to 1", 1, owner} {}
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
void RaiseDead::expend(shared_ptr<Minion> minion) {
    // TODO: Handle exception
    return;
}
void RaiseDead::expend(shared_ptr<Ritual> ritual) {
    // TODO: Handle exception
    return;
}

Blizzard::Blizzard(int owner) : Spell{"Blizzard", "Deal 2 damage to all minions", 3, owner} {}
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
void Blizzard::expend(shared_ptr<Minion> minion) {
    // TODO: Handle exception
    return;
}
void Blizzard::expend(shared_ptr<Ritual> ritual) {
    // TODO: Handle exception
    return;
}
