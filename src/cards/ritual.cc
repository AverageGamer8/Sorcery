#include "ritual.h"

#include <iostream>  // TODO: remove debug
#include <memory>
#include <string>

#include "../gameModel/game.h"

using namespace std;

Ritual::Ritual(string name, string description, int cost, int owner, Game* game,
               shared_ptr<TriggeredAbility> triggerAbility, int activationCost, int charges, string type)
    : Card{name, description, type, cost, owner, game}, triggerAbility{triggerAbility}, activationCost{activationCost}, charges{charges} {}

string Ritual::getName() const { return name; }

string Ritual::getDesc() const { return description; }

string Ritual::getType() const { return type; }

int Ritual::getCost() const { return cost; }

int Ritual::getCharges() const { return charges; }

int Ritual::getActivationCost() const { return activationCost; }

void Ritual::setCharges(int charges) {
    this->charges = charges;
}

void Ritual::attachAbilities() {
    if (!triggerAbility) return;
    game->getTrigger(triggerAbility->getTriggerType()).attach(triggerAbility);
    cout << "DEBUG: Ritual: attached trigger." << endl;
}
void Ritual::detachAbilities() {
    if (!triggerAbility) return;
    game->getTrigger(triggerAbility->getTriggerType()).detach(triggerAbility);
}

DarkRitual::DarkRitual(int owner, Game* game)
    : Ritual{"Dark Ritual", "At the start of your turn, gain 1 magic", 0, owner, game,
             make_shared<OnStartGainMagic>(game, owner), 1, 5} {}

AuraOfPower::AuraOfPower(int owner, Game* game)
    : Ritual{"Aura of Power", "Whenever a minion enters play under your control, it gains +1/+1", 1, owner, game,
             make_shared<OnEnterBuff>(game, owner), 1, 4} {}

Standstill::Standstill(int owner, Game* game)
    : Ritual{"Standstill", "Whenever a minion enters play, destroy it", 3, owner, game,
             make_shared<OnEnterDestroy>(game, owner), 2, 4} {}
