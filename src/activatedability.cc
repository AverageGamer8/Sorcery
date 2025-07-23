#include "activatedability.h"

#include <iostream>  // TODO: remove debugs
#include <memory>

#include "./gameModel/game.h"

using namespace std;

int ActivatedAbility::getCost() const { return cost; }

DealDamage::DealDamage(shared_ptr<Game> game) : ActivatedAbility(game, "Deal 1 damage to target minion", 1) {}
bool DealDamage::activate() {
    cout << "DEBUG: (ActivatedAbility) Not proper usage: must have target." << endl;
    return false;
}
bool DealDamage::activate(int target) {
    auto p = game->getInactivePlayer();
    auto minion = p->getBoard()->getMinion(target);
    minion->takeDamage(1);
    return true;
}

SummonAirElemental::SummonAirElemental(shared_ptr<Game> game) : ActivatedAbility(game, "Summon a 1/1 air elemental", 1) {}
bool SummonAirElemental::activate() {
    auto p = game->getActivePlayer();
    if (p->getBoard()->isFull()) {
        cout << "DEBUG: (ActivatedAbility) Cannot summon minions, board full." << endl;
        return false;
    }
    int index = game->getActiveIndex();
    p->getBoard()->addMinion(make_shared<AirElemental>(index, game));
    return true;
}
bool SummonAirElemental::activate(int target) {
    cout << "DEBUG: (ActivatedAbility) Not proper usage: should not have target." << endl;
    return false;
}

SummonThreeAirElemental::SummonThreeAirElemental(shared_ptr<Game> game) : ActivatedAbility(game, "Summon up to three 1/1 air elementals", 2) {}
bool SummonThreeAirElemental::activate() {
    auto p = game->getActivePlayer();
    if (p->getBoard()->isFull()) {
        cout << "DEBUG: (ActivatedAbility) Cannot summon minions, board full." << endl;
        return false;
    }
    // If over 5, board will handle.
    int index = game->getActiveIndex();
    p->getBoard()->addMinion(make_shared<AirElemental>(index, game));
    p->getBoard()->addMinion(make_shared<AirElemental>(index, game));
    p->getBoard()->addMinion(make_shared<AirElemental>(index, game));
    return true;
}
bool SummonThreeAirElemental::activate(int target) {
    cout << "DEBUG: (ActivatedAbility) Not proper usage: should not have target." << endl;
    return false;
}