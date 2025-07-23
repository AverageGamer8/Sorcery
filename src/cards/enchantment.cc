#include "enchantment.h"

#include <memory>
#include <string>
#include <iostream> // debug

#include "../gameModel/game.h"
#include "../gameModel/player.h"
#include "card.h"
using namespace std;

Enchantment::Enchantment(string name, string description, int cost, int owner, Game* game,
                         int atk, int def, int actions, string atkDesc, string defDesc, string type): 
    Minion{name, description, cost, owner, game, atk, def, actions, type}, atkDesc{atkDesc}, defDesc{defDesc} {}

bool Enchantment::attach(int player, int target) {
    minion = game->getPlayer(player)->getBoard()->getMinion(target);
    return minion != nullptr;
}

bool Enchantment::activate() {
    // maybe instead use getActivatedAbility to go and grab it?
    // and have this method just handle actions?
    return true;
}

bool Enchantment::activate(int target) {
    //minion->activate(target); doesnt exist yet?

    return true;
}

void Enchantment::restoreAction() {
    actions = 0; // actions of an enchantment can be negative
    minion->restoreAction();
}

void Enchantment::takeDamage(int dmg) {
    def -= dmg;
    if (def < 0) {
        minion->takeDamage(-def);
        def = 0;
    }
}

shared_ptr<Minion> Enchantment::getMinion() const {
    return minion;
}

string Enchantment::getName() const {
    if (minion == nullptr) return name;
    else return minion->getName();
}

string Enchantment::getDesc() const {
    if (minion == nullptr) return description;
    else return minion->getDesc();
}

string Enchantment::getType() const {
    return type;
}

int Enchantment::getCost() const {
    if (minion == nullptr) return cost;
    else return minion->getCost();
}
string Enchantment::getEnchName() const {
    return name;
}
string Enchantment::getEnchDesc() const {
    return description;
}
int Enchantment::getEnchCost() const {
    return cost;
}

int Enchantment::getAttack() const {
    return atk + minion->getAttack();
}
int Enchantment::getDefence() const {
    return def + minion->getDefence();
}
int Enchantment::getActions() const {
    return actions + minion->getActions(); // getActions get cumulative actions available
}
string Enchantment::getAtkDesc() const {
    return atkDesc;
}
string Enchantment::getDefDesc() const {
    return defDesc;
}

void Enchantment::consumeAction() {
    if (actions > 0) actions--;
    else minion->consumeAction();
}

// Specific Enchantments
GiantStrength::GiantStrength(int owner, Game* game): Enchantment{"Giant Strength", "", 1, owner, game, 2, 2, 0, "+2", "+2"} { }
Enrage::Enrage(int owner, Game* game): Enchantment{"Enrage", "", 2, owner, game, 0, 0, 0, "*2", "*2"} { }
bool Enrage::attach(int player, int target) {
    minion = game->getPlayer(player)->getBoard()->getMinion(target);
    if (minion != nullptr) {
        atk = minion->getAttack() * 1;
        def = minion->getDefence() * 1;
        return true;
    }
    return false;
}
Haste::Haste(int owner, Game* game): Enchantment{"Haste", "Enchanted minion gains +1 action per turn", 1, owner, game, 0, 0, 1} { }
void Haste::restoreAction() {
    if (actions < 1) actions = 1;
    minion->restoreAction();
}
MagicFatigue::MagicFatigue(int owner, Game* game): Enchantment{"MagicFatigue", "Enchanted minion's activated ability costs 2 more", 1, owner, game, 0, 0, 0} { }
bool MagicFatigue::activate() { // override activate ability with same ability but costs 2 more
    // check if magic >= cost + 2, dont activate if not
    // go through game? find active player check magic
    int curMP = game->getActivePlayer()->getMagic();
    // get base ability cost
    // get enchantment ability cost
    return true;
}
bool MagicFatigue::activate(int target) {
    // check if magic >= cost + 2, dont activate if not
    int curMP = game->getActivePlayer()->getMagic();
    return true;
}
Silence::Silence(int owner, Game* game): Enchantment{"Silence", "Enchanted minion cannot use abilities", 1, owner, game, 0, 0, 0} { }
bool Silence::activate() {
    cout << "Blocked by Silence Enchantment." << endl;
    return false; // your not getting that
}
bool Silence::activate(int target) {
    cout << "Blocked by Silence Enchantment." << endl;
    return false;
}

