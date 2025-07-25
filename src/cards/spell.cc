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
    p->getBoard()->removeMinion(target);
    game->notifyTrigger(Trigger::TriggerType::MinionExit);
    return true;
}
bool Banish::expend(int player) {
    game->getPlayer(player)->getBoard()->removeRitual();
    return true;
}

Unsummon::Unsummon(int owner, Game* game) : Spell{"Unsummon", "Return target minion to its owner's hand", 1, owner, game} {}
bool Unsummon::expend() {
    throw ArgException("Unsummon must be used on minions.");
}
bool Unsummon::expend(int player, int minion) {
    auto p = game->getPlayer(player);
    if (p->getHand()->isFull()) {
        Narrator::announce(p->getName() + " tried to expend Unsummon, but their hand is full.");
        throw ArgException("Can't Unsummon, " + p->getName() + "'s hand is full.");
    }
    game->notifyTrigger(Trigger::TriggerType::MinionExit);
    p->getHand()->addCard(p->getBoard()->removeMinion(minion));
    return true;
}
bool Unsummon::expend(int player) {
    throw ArgException("Unsummon must be used on minions.");
}

Recharge::Recharge(int owner, Game* game) : Spell{"Recharge", "Your ritual gains 3 charges", 1, owner, game} {}
bool Recharge::expend() {
    auto ritual = game->getPlayer(owner)->getBoard()->getRitual();
    if (!ritual) {
        throw ArgException("Ritual is invalid.");
    }
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
    game->getPlayer(player)->getBoard()->setMinion(minion, ench->getMinion());
    return true;
}
bool Disenchant::expend(int player) {
    throw ArgException("No enchantments on minion selected.");
}

RaiseDead::RaiseDead(int owner, Game* game) : Spell{"Raise Dead", "Resurrect the top minion in your graveyard and set its defence to 1", 1, owner, game} {}
bool RaiseDead::expend() {
    auto curr = game->getPlayer(game->getActiveIndex());
    if (curr->getHand()->isFull()) {
        throw ArgException("Hand is full.");
    }
    if (curr->getGraveyard()->isEmpty()) {
        throw ArgException("Graveyard is empty.");
    }

    auto m = curr->getGraveyard()->popTopMinion();
    m->setDefence(1);
    curr->getHand()->addCard(static_pointer_cast<Card>(m));
    return true;
}
bool RaiseDead::expend(int player, int minion) {
    throw ArgException("Riase Dead must be used without target.");
}
bool RaiseDead::expend(int player) {
    throw ArgException("Riase Dead must be used without target.");
}

Blizzard::Blizzard(int owner, Game* game) : Spell{"Blizzard", "Deal 2 damage to all minions", 3, owner, game} {}
bool Blizzard::expend() {
    auto curr = game->getPlayer(game->getActiveIndex());
    auto opp = game->getPlayer(game->getInactiveIndex());
    auto& currMinions = curr->getBoard()->getMinions();
    auto& oppMinions = opp->getBoard()->getMinions();
    auto currSize = currMinions.size();
    auto oppSize = oppMinions.size();
    for (size_t i = 0; i < currSize;) {
        if (currMinions[i]->takeDamage(2)) {
            game->handleMinionDeath(game->getActiveIndex(), i);
            currSize--;
            currMinions = curr->getBoard()->getMinions();
        } else
            i++;
    }
    for (size_t i = 0; i < oppSize;) {
        if (oppMinions[i]->takeDamage(2)) {
            game->handleMinionDeath(game->getInactiveIndex(), i);
            oppSize--;
            oppMinions = opp->getBoard()->getMinions();
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
