#include "enchantment.h"

#include <memory>
#include <string>

#include "../gameModel/game.h"
#include "../gameModel/player.h"
#include "card.h"
using namespace std;

Enchantment::Enchantment(string name, string description, int cost, int owner, int atk, int def, int actions, string atkDesc, string defDesc): 
    Minion{name, description, "Enchantment", cost, owner, atk, def, actions}, atkDesc{atkDesc}, defDesc{defDesc} {}

void Enchantment::attach(shared_ptr<Minion> target) {
    minion = target;
}

void Enchantment::attack() {
    Game* g = game.get();
    Player* opp = g->getPlayer(g->getInactiveIndex());

    opp->life -= atk + minion->getAttack();
}

void Enchantment::attack(int target) {
    Game* g = game.get();
    Player* opp = g->getPlayer(g->getInactiveIndex());

    opp->minions[target - 1].get()->defence -= minion->getAttack();
    defence -= opp->minions[target - 1].get()->atk;
}

void Enchantment::activate() {
    minion->activate();
}

void Enchantment::activate(int target) {
    minion->activate(target);
}

void Enchantment::restoreAction() {
    minion->restoreAction();
}

void Enchantment::getHit(int dmg) {
    defence -= dmg;
    if (def < 0) {
        minion->getHit(-def);
        def = 0;
    }
}

shared_ptr<Minion> Enchantment::getMinion() const {
    return minion;
}

string Enchantment::getName() const {
    return name;
}

string Enchantment::getDesc() const {
    return description;
}

string Enchantment::getType() const {
    return type;
}

int Enchantment::getCost() const {
    return cost;
}
int Enchantment::getAttack() const {
    return atk + minion->getAttack();
}
int Enchantment::getDefence() const {
    return defence + minion->getDefence;
}
string& Enchantment::getAtkDesc() const {
    return atkDesc;
}
string& Enchantment::getDefDesc() const {
    return defDesc;
}

// Specific Enchantments
GiantStrength::GiantStrength(int owner): Enchantment{"Giant Strength", "", "Enchantment", 1, owner, 2, 2, 0, "+2", "+2"} { }
Enrage::Enrage(int owner): Enchantment{"Enrage", "", "Enchantment", 2, owner, 0, 0, 0, "*2", "*2"} { }
void Enrage::attach(shared_ptr<Minion> target) {
    minion = target;
    atk = target->getAttack() * 1;
    defence = target->getDefence() * 1;
}
Haste::Haste(int owner): Enchantment{"Haste", "Enchanted minion gains +1 action per turn", "Enchantment", 1, owner, 0, 0, 1} { }
void Haste::restoreAction() {
    minion->restoreAction();
    if (actions < 1) actions = 1;
}
MagicFatigue::MagicFatigue(int owner): Enchantment{"MagicFatigue", "Enchanted minion's activated ability costs 2 more", "Enchantment", 1, owner, 0, 0, 0} { }
void MagicFatigue::activate() { // override activate ability with same ability but costs 2 more
    // check if magic >= cost + 2, dont activate if not
    // go through game? find active player check magic
    int curMP = game->getActivePlayer()->getMagic();
    // get base ability cost
    // get enchantment ability cost
}
void MagicFatigue::activate(int target) {
    // check if magic >= cost + 2, dont activate if not
    int curMP = game->getActivePlayer()->getMagic();

}
Silence::Silence(int owner): Enchantment{"Silence", "Enchanted minion cannot use abilities", "Enchantment", 1, owner, 0, 0, 0} { }
void Silence::activate() {
    return; // your not getting that
}
void Silence::activate(int target) {
    return;
}

