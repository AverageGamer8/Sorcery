#include "enchantment.h"

#include <memory>
#include <string>
#include <iostream> // debug

#include "../gameModel/game.h"
#include "../gameModel/player.h"
#include "card.h"
using namespace std;

Enchantment::Enchantment(string name, string description, int cost, int owner, shared_ptr<Game> game,
                         int atk, int def, int actions, string atkDesc, string defDesc, string type): 
    Minion{name, description, cost, owner, game, atk, def, actions, type}, atkDesc{atkDesc}, defDesc{defDesc} {}

void Enchantment::attach(shared_ptr<Minion> target) {
    minion = target;
}

void Enchantment::attack() {
    if (getActions() == 0) { 
        cout << "DEBUG: (Minion) " << name << " is out of actions." << endl;
        return;
    }
    shared_ptr<Player> opp = game->getPlayer(game->getInactiveIndex());
    opp->setLife(opp->getLife() - getAttack());
    if (opp->getLife() <= 0) {
        opp->setLife(0);
        game->setWinner(game->getActiveIndex());
    }
    --actions;
}

void Enchantment::attack(int target, shared_ptr<Minion> self) {
     if (actions == 0) { 
        cout << "DEBUG: (Minion) " << name << " is out of actions." << endl;
        return;
    }
    game->battleMinion(self, target);
    --actions;
}

void Enchantment::activate() {
    //minion->activate(); doesnt exist yet?
}

void Enchantment::activate(int target) {
    //minion->activate(target); doesnt exist yet?
}

void Enchantment::restoreAction() {
    if (actions < 0) actions = 0;
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
    return def + minion->getDefence();
}
int Enchantment::getActions() const {
    return actions + minion->getActions();
}
string Enchantment::getAtkDesc() const {
    return atkDesc;
}
string Enchantment::getDefDesc() const {
    return defDesc;
}

// Specific Enchantments
GiantStrength::GiantStrength(int owner, shared_ptr<Game> game): Enchantment{"Giant Strength", "", 1, owner, game, 2, 2, 0, "+2", "+2"} { }
Enrage::Enrage(int owner, shared_ptr<Game> game): Enchantment{"Enrage", "", 2, owner, game, 0, 0, 0, "*2", "*2"} { }
void Enrage::attach(shared_ptr<Minion> target) {
    minion = target;
    atk = minion->getAttack() * 1;
    def = minion->getDefence() * 1;
}
Haste::Haste(int owner, shared_ptr<Game> game): Enchantment{"Haste", "Enchanted minion gains +1 action per turn", 1, owner, game, 0, 0, 1} { }
void Haste::restoreAction() {
    if (actions < 1) actions = 1;
    minion->restoreAction();
}
MagicFatigue::MagicFatigue(int owner, shared_ptr<Game> game): Enchantment{"MagicFatigue", "Enchanted minion's activated ability costs 2 more", 1, owner, game, 0, 0, 0} { }
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
Silence::Silence(int owner, shared_ptr<Game> game): Enchantment{"Silence", "Enchanted minion cannot use abilities", 1, owner, game, 0, 0, 0} { }
void Silence::activate() {
    return; // your not getting that
}
void Silence::activate(int target) {
    return;
}

