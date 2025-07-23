#include "spell.h"

#include <iostream>  // TODO: DEBUG
#include <string>

#include "../gameModel/game.h"
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
    // TODO: Handle exception - should never be played
    cout << "DEBUG: (Spell) Not proper usage: must have proper target." << endl;
    return false;
}
bool Banish::expend(int player, int target) {
    auto p = game->getPlayer(player);
    p->getBoard()->removeMinion(target);
    return true;
}
bool Banish::expend(int player) {
    game->getPlayer(player)->getBoard()->removeRitual();
    return true;
}

Unsummon::Unsummon(int owner, Game* game) : Spell{"Unsummon", "Return target minion to its owner's hand", 1, owner, game} {}
bool Unsummon::expend() {
    // TODO: Handle exception
    cout << "DEBUG: (Spell) Not proper usage: must be used on minions." << endl;
    return false;
}
bool Unsummon::expend(int player, int minion) {
    auto p = game->getPlayer(player);
    if (p->getHand()->isFull()) {
        // TODO: Handle exception - hand full
        cout << "DEBUG: (Spell) Can't Unsummon, " << p->getName() << "'s hand is full." << endl;
        return false;
    }
    p->getHand()->addCard(p->getBoard()->getMinion(minion));
    p->getBoard()->removeMinion(minion);
    return true;
}
bool Unsummon::expend(int player) {
    // TODO: Handle exception
    cout << "DEBUG (Spell) Not proper usage: must be used on minions." << endl;
    return false;
}

Recharge::Recharge(int owner, Game* game) : Spell{"Recharge", "Your ritual gains 3 charges", 1, owner, game} {}
bool Recharge::expend() {
    cout << "DEBUG (Spell) Not proper usage: must be used on rituals." << endl;
    // TODO: Handle exception
    return false;
}
bool Recharge::expend(int player, int minion) {
    // TODO: Handle exception
    cout << "DEBUG (Spell) Not proper usage: must be used on rituals." << endl;
    return false;
}
bool Recharge::expend(int player) {
    auto ritual = game->getPlayer(player)->getBoard()->getRitual();
    if (!ritual) {
        cout << "DEBUG (Spell) Ritual is invalid." << endl;
        return false;
    }
    ritual->setCharges(ritual->getCharges() + 3);
    return true;
}

Disenchant::Disenchant(int owner, Game* game) : Spell{"Disenchant", "Destroy the top enchantment on target minion", 1, owner, game} {}
bool Disenchant::expend() {
    // TODO: Handle exception
    cout << "DEBUG (Spell) Not proper usage: must be used on minions." << endl;
    return false;
}
bool Disenchant::expend(int player, int minion) {
    auto target = game->getPlayer(player)->getBoard()->getMinion(minion);
    if (!target) {
        cout << "No minion selected" << endl;
        return false;
    }
    if (target->getType() != "Enchantment") {
        cout << "No enchantments on minion selected" << endl;
        return false;
    }
    auto ench = static_pointer_cast<Enchantment>(target);
    game->getPlayer(player)->getBoard()->setMinion(minion, ench->getMinion());
    return true;
}
bool Disenchant::expend(int player) {
    // TODO: Handle exception
    cout << "DEBUG (Spell) Not proper usage: must be used on minions." << endl;
    return false;
}

RaiseDead::RaiseDead(int owner, Game* game) : Spell{"RaiseDead", "Resurrect the top minion in your graveyard and set its defence to 1", 1, owner, game} {}
bool RaiseDead::expend() {
    auto curr = game->getPlayer(game->getActiveIndex());
    if (curr->getHand()->isFull()) {
        // TODO: Handle exception
        cout << "DEBUG (Spell) Hand is full." << endl;
        return false;
    }
    if (curr->getGraveyard()->isEmpty()) {
        // TODO: Handle exception
        cout << "DEBUG (Spell) Graveyard is empty." << endl;
        return false;
    }

    auto m = curr->getGraveyard()->popTopMinion();
    m->setDefence(1);
    curr->getHand()->addCard(static_pointer_cast<Card>(m));
    return true;
}
bool RaiseDead::expend(int player, int minion) {
    // TODO: Handle exception
    cout << "DEBUG (Spell) Not proper usage: must be used without target." << endl;
    return false;
}
bool RaiseDead::expend(int player) {
    // TODO: Handle exception
    cout << "DEBUG (Spell) Not proper usage: must be used without target." << endl;
    return false;
}

Blizzard::Blizzard(int owner, Game* game) : Spell{"Blizzard", "Deal 2 damage to all minions", 3, owner, game} {}
bool Blizzard::expend() {
    auto curr = game->getPlayer(game->getActiveIndex());
    auto opp = game->getPlayer(game->getInactiveIndex());
    for (auto& minion : curr->getBoard()->getMinions()) {
        minion->takeDamage(2);
    }
    for (auto& minion : opp->getBoard()->getMinions()) {
        minion->takeDamage(2);
    }
}
bool Blizzard::expend(int player, int minion) {
    // TODO: Handle exception
    cout << "DEBUG (Spell) Not proper usage: must be used without target." << endl;
    return false;
}
bool Blizzard::expend(int player) {
    // TODO: Handle exception
    cout << "DEBUG (Spell) Not proper usage: must be used without target." << endl;
    return false;
}
