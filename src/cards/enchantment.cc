#include "enchantment.h"


#include "../gameModel/game.h"
using namespace std;

Enchantment::Enchantment(string name, string description, int cost, int owner, Game* game,
                         int atk, int def, int actions, shared_ptr<ActivatedAbility> activatedAbility, 
                         shared_ptr<TriggeredAbility> triggeredAbility, string atkDesc, string defDesc, string type) : 
    Minion{name, description, cost, owner, game, atk, def, actions, activatedAbility, triggeredAbility, 
        type}, atkDesc{atkDesc}, defDesc{defDesc} {}

bool Enchantment::attach(int player, int target) {
    minion = game->getPlayer(player)->getBoard()->getMinion(target);
    if (minion != nullptr) {
        game->getPlayer(player)->getBoard()->setMinion(target, shared_from_this());
        return true;
    }
    return false;
}

bool Enchantment::activate() {
    return minion->activate();
}

bool Enchantment::activate(int player, int target) {
    return minion->activate(player, target);
}

void Enchantment::restoreAction() {
    actions = 0;
    minion->restoreAction();
}

bool Enchantment::takeDamage(int dmg) {
    def -= dmg;
    if (def < 0) {
        int remaining = -def;
        def = 0;
        return minion->takeDamage(remaining);
    }
    return false;
}

void Enchantment::increaseAtk(int amount) {
    minion->increaseAtk(amount);
}
void Enchantment::increaseDef(int amount) {
    minion->increaseDef(amount);
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

int Enchantment::getAttack() const { // gets cumulative atk
    return atk + minion->getAttack();
}
int Enchantment::getDefence() const { // gets cumulative def
    return def + minion->getDefence();
}
int Enchantment::getActions() const {
    return actions + minion->getActions(); // get cumulative actions available
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

shared_ptr<ActivatedAbility> Enchantment::getActivatedAbility() const {
    return minion->getActivatedAbility();
}
shared_ptr<TriggeredAbility> Enchantment::getTriggeredAbility() const {
    return minion->getTriggeredAbility();
}
int Enchantment::getActivateCost() const {
    return minion->getActivateCost();
}

// Specific Enchantments
GiantStrength::GiantStrength(int owner, Game* game): Enchantment{"Giant Strength", "", 1, owner, game, 2, 2, 0, nullptr, nullptr, "+2", "+2"} { }
Enrage::Enrage(int owner, Game* game): Enchantment{"Enrage", "", 2, owner, game, 0, 0, 0, nullptr, nullptr, "*2", "*2"} { }
bool Enrage::attach(int player, int target) {
    minion = game->getPlayer(player)->getBoard()->getMinion(target);
    if (minion != nullptr) {
        game->getPlayer(player)->getBoard()->setMinion(target, shared_from_this());
        atk = minion->getAttack() * 1;
        def = minion->getDefence() * 1;
        return true;
    }
    return false;
}
Haste::Haste(int owner, Game* game): Enchantment{"Haste", "Enchanted minion gains +1 action per turn", 1, owner, game, 0, 0, 1, nullptr, nullptr} { }
void Haste::restoreAction() {
    if (actions < 1) actions = 1;
    minion->restoreAction();
}
MagicFatigue::MagicFatigue(int owner, Game* game): Enchantment{"Magic Fatigue", "Enchanted minion's activated ability costs 2 more", 1, owner, game, 0, 0, 0, nullptr, nullptr} { }
int MagicFatigue::getActivateCost() const {
    return minion->getActivateCost() + 2;
}
Silence::Silence(int owner, Game* game): Enchantment{"Silence", "Enchanted minion cannot use abilities", 1, owner, game, 0, 0, 0, nullptr, nullptr} { }
bool Silence::activate() {
    return false;
}
bool Silence::activate(int player, int target) {
    return false;
}
