#include "spell.h"

#include <string>

#include "../argexception.h"
#include "../gameModel/game.h"
#include "../narrator.h"
#include "card.h"
#include "enchantment.h"
using namespace std;

Spell::Spell(string name, string description, int cost, int owner, Game* game, string type) : Card{name, description, type, cost, owner, game} {};

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
Banish::Banish(int owner, Game* game) : Spell{"Banish", "Destroy target minion or ritual", 2, owner, game} {}
bool Banish::expend() {
    throw ArgException("Banish must have proper target.");
}
bool Banish::expend(int player, int target) {
    auto p = game->getPlayer(player);
    game->notifyTrigger(Trigger::TriggerType::MinionExit);
    auto m = p->getBoard()->removeMinion(target);
    Narrator::announce(p->getName() + "'s " + m->getName() + " has been banished.");
    return true;
}
bool Banish::expend(int player) {
    auto p = game->getPlayer(player);
    Narrator::announce(p->getName() + "'s " + p->getBoard()->getRitual()->getName() + " has been banished.");
    p->getBoard()->removeRitual();
    return true;
}

Unsummon::Unsummon(int owner, Game* game) : Spell{"Unsummon", "Return target minion to its owner's hand", 1, owner, game} {}
bool Unsummon::expend() {
    throw ArgException("Unsummon must be used on minions.");
}
bool Unsummon::expend(int player, int minion) {
    auto p = game->getPlayer(player);
    if (p->isHandFull()) {
        Narrator::announce(p->getName() + " tried to expend Unsummon, but their hand is full.");
        throw ArgException("Can't Unsummon, " + p->getName() + "'s hand is full.");
    }
    game->notifyTrigger(Trigger::TriggerType::MinionExit);
    auto m = p->getBoard()->removeMinion(minion);
    Narrator::announce(p->getName() + "'s " + m->getName() + " has been returned to their hand.");
    p->getHand()->addCard(m);
    return true;
}
bool Unsummon::expend(int player) {
    throw ArgException("Unsummon must be used on minions.");
}

Recharge::Recharge(int owner, Game* game) : Spell{"Recharge", "Your ritual gains 3 charges", 1, owner, game} {}
bool Recharge::expend() {
    auto player = game->getPlayer(owner);
    if (!player->hasRitual()) {
        throw ArgException("No ritual to target.");
    }
    auto ritual = player->getBoard()->getRitual();
    Narrator::announce(player->getName() + "'s " + ritual->getName() + " has been charged up by 3 charges.");
    ritual->setCharges(ritual->getCharges() + 3);
    return true;
}
bool Recharge::expend(int player, int minion) {
    throw ArgException("Recharge must be used on rituals.");
}
bool Recharge::expend(int player) {
    throw ArgException("Recharge must be used on rituals.");
}

Disenchant::Disenchant(int owner, Game* game) : Spell{"Disenchant", "Destroy the top enchantment on target minion", 1, owner, game} {}
bool Disenchant::expend() {
    throw ArgException("Disenchant must be used on minions.");
}
bool Disenchant::expend(int player, int minion) {
    auto target = game->getPlayer(player)->getBoard()->getMinion(minion);
    if (!target) {
        throw ArgException("No minion selected.");
    }
    if (target->getType() != "Enchantment") {
        throw ArgException("No enchantments on minion selected.");
    }
    auto ench = static_pointer_cast<Enchantment>(target);
    auto m = ench->getMinion();
    Narrator::announce(target->getName() + "'s " + ench->getEnchName() + " has been removed.");
    game->getPlayer(player)->getBoard()->setMinion(minion, ench->getMinion());
    return true;
}
bool Disenchant::expend(int player) {
    throw ArgException("No enchantments on minion selected.");
}

RaiseDead::RaiseDead(int owner, Game* game) : Spell{"Raise Dead", "Resurrect the top minion in your graveyard and set its defence to 1", 1, owner, game} {}
bool RaiseDead::expend() {
    auto curr = game->getPlayer(owner);
    if (curr->getHand()->isFull()) {
        throw ArgException("Hand is full.");
    }
    if (curr->isGraveyardEmpty()) {
        throw ArgException("Graveyard is empty.");
    }

    auto m = curr->getGraveyard()->popTopMinion();
    m->setDefence(1);
    Narrator::announce(curr->getName() + "'s " + m->getName() + " has been resurrected and returned to their hand.");
    curr->getHand()->addCard(static_pointer_cast<Card>(m));
    return true;
}
bool RaiseDead::expend(int player, int minion) {
    throw ArgException("Raise Dead must be used without target.");
}
bool RaiseDead::expend(int player) {
    throw ArgException("Raise Dead must be used without target.");
}

Blizzard::Blizzard(int owner, Game* game) : Spell{"Blizzard", "Deal 2 damage to all minions", 3, owner, game} {}
bool Blizzard::expend() {
    auto curr = game->getPlayer(game->getActiveIndex());
    auto opp = game->getPlayer(game->getInactiveIndex());
    auto& currMinions = curr->getBoard()->getMinions();
    auto& oppMinions = opp->getBoard()->getMinions();
    for (size_t i = 0; i < currMinions.size();) {
        if (currMinions[i]->takeDamage(2)) {
            game->handleMinionDeath(game->getActiveIndex(), i);
        } else
            i++;
    }
    for (size_t i = 0; i < oppMinions.size();) {
        if (oppMinions[i]->takeDamage(2)) {
            game->handleMinionDeath(game->getInactiveIndex(), i);
        } else
            i++;
    }
    return true;
}
bool Blizzard::expend(int player, int minion) {
    throw ArgException("Blizzard must be used without target.");
}
bool Blizzard::expend(int player) {
    throw ArgException("Blizzard must be used without target.");
}
