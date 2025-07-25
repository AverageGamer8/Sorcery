#include "activatedability.h"

#include <iostream>  // TODO: remove debugs
#include <memory>

#include "../../gameModel/game.h"
#include "../../narrator.h"
#include "../../argexception.h"

using namespace std;

int ActivatedAbility::getCost() const { return cost; }

DealDamage::DealDamage(Game* game) : ActivatedAbility(game, "Deal 1 damage to target minion", 1) {}
bool DealDamage::activate() {
    throw ArgException("Must have target.");
}
bool DealDamage::activate(int player, int minion) {
    auto p = game->getPlayer(player);
    auto m = p->getBoard()->getMinion(minion);
    m->takeDamage(1);
    Narrator::announce(p->getName() + "'s " + m->getName() + " takes 1 damage from an activated ability.");
    if (m->getDefence() <= 0) {
        game->handleMinionDeath(player, minion);
    }
    return true;
}

SummonAirElemental::SummonAirElemental(Game* game) : ActivatedAbility(game, "Summon a 1/1 air elemental", 1) {}
bool SummonAirElemental::activate() {
    auto p = game->getActivePlayer();
    if (p->getBoard()->isFull()) {
        Narrator::announce(p->getName() + " tried to summon Air Elementals, but their board is full.");
        throw ArgException("Cannot summon minions, " + p->getName() + "'s board is full.");
    }
    int index = game->getActiveIndex();
    p->getBoard()->addMinion(make_shared<AirElemental>(index, game));
    game->notifyTrigger(Trigger::TriggerType::MinionEnter);
    Narrator::announce(p->getName() + " summons a 1/1 Air Elemental.");
    return true;
}
bool SummonAirElemental::activate(int player, int minion) {
    throw ArgException("Should not have target.");
}

SummonThreeAirElemental::SummonThreeAirElemental(Game* game) : ActivatedAbility(game, "Summon up to three 1/1 air elementals", 2) {}
bool SummonThreeAirElemental::activate() {
    auto p = game->getActivePlayer();
    if (p->getBoard()->isFull()) {
        Narrator::announce(p->getName() + " tried to summon an Air Elemental, but their board is full.");
        throw ArgException("Cannot summon minions, " + p->getName() + "'s board is full.");
    }
    int index = game->getActiveIndex();
            game->notifyTrigger(Trigger::TriggerType::MinionEnter);
            
    Narrator::announce(p->getName() + " summons up to three 1/1 Air Elementals in a gust of magic.");
    for (int i = 0; i < 3; i++) {
        if (!p->getBoard()->isFull()) {
            p->getBoard()->addMinion(make_shared<AirElemental>(index, game));
            game->notifyTrigger(Trigger::TriggerType::MinionEnter);
            Narrator::announce(p->getName() + " summons an Air Elemental in a massive gust of magic.");
        }
    }
    return true;
}
bool SummonThreeAirElemental::activate(int player, int minion) {
    throw ArgException("Should not have target.");
}