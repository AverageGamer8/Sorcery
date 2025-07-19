#include "spell.h"
#include "card.h"
#include "minion.h"
#include <string>
using namespace std;

Spell::Spell(string name, string description, string type, int cost, int owner) : Card{name, description, type, cost, owner} {};

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
Banish::Banish(int owner) : Spell{"Banish", "Destroy target minion or ritual", "Spell", 2, owner} {}

Unsummon::Unsummon(int owner) : Spell{"Unsummon", "Return target minion to its owner's hand", "Spell", 1, owner} {}

Recharge::Recharge(int owner) : Spell{"Recharge", "Your ritual gains 3 charges", "Spell", 1, owner} {}

Disenchant::Disenchant(int owner) : Spell{"Disenchant", "Destroy the top enchantment on target minion", "Spell", 1, owner} {}

RaiseDead::RaiseDead(int owner) : Spell{"RaiseDead", "Resurrect the top minion in your graveyard and set its defence to 1", "Spell", 1, owner} {}

Blizzard::Blizzard(int owner) : Spell{"Blizzard", "Deal 2 damage to all minions", "Spell", 3, owner} {}
