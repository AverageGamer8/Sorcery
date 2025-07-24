#include "activatedability.h"

#include <iostream>  // TODO: remove debugs
#include <memory>

#include "../../gameModel/game.h"

using namespace std;

int ActivatedAbility::getCost() const { return cost; }

DealDamage::DealDamage(Game* game) : ActivatedAbility(game, "Deal 1 damage to target minion", 1) {}
bool DealDamage::activate() {
    cout << "DEBUG: (ActivatedAbility) Not proper usage: must have target." << endl;
    return false;
}
bool DealDamage::activate(int player, int minion) {
    auto p = game->getPlayer(player);
    auto m = p->getBoard()->getMinion(minion);
    m->takeDamage(1);
    if (m->getDefence() <= 0) {
        game->handleMinionDeath(player, minion);
    }
    return true;
}

SummonAirElemental::SummonAirElemental(Game* game) : ActivatedAbility(game, "Summon a 1/1 air elemental", 1) {}
bool SummonAirElemental::activate() {
    auto p = game->getActivePlayer();
    if (p->getBoard()->isFull()) {
        cout << "DEBUG: (ActivatedAbility) Cannot summon minions, board full." << endl;
        return false;
    }
    int index = game->getActiveIndex();
    p->getBoard()->addMinion(make_shared<AirElemental>(index, game));
    game->notifyTrigger(Trigger::TriggerType::MinionEnter);
    return true;
}
bool SummonAirElemental::activate(int player, int minion) {
    cout << "DEBUG: (ActivatedAbility) Not proper usage: should not have target." << endl;
    return false;
}

SummonThreeAirElemental::SummonThreeAirElemental(Game* game) : ActivatedAbility(game, "Summon up to three 1/1 air elementals", 2) {}
bool SummonThreeAirElemental::activate() {
    auto p = game->getActivePlayer();
    if (p->getBoard()->isFull()) {
        cout << "DEBUG: (ActivatedAbility) Cannot summon minions, board full." << endl;
        return false;
    }
    int index = game->getActiveIndex();
    for (int i = 0; i < 3; i++) {
        if (!p->getBoard()->isFull()) {
            p->getBoard()->addMinion(make_shared<AirElemental>(index, game));
            game->notifyTrigger(Trigger::TriggerType::MinionEnter);
        }
    }
    return true;
}
bool SummonThreeAirElemental::activate(int player, int minion) {
    cout << "DEBUG: (ActivatedAbility) Not proper usage: should not have target." << endl;
    return false;
}