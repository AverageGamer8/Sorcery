#include "minion.h"

#include <iostream>  // todo remove debug
#include <memory>
#include <string>

#include "../gameModel/game.h"
#include "../gameModel/player.h"
#include "card.h"
using namespace std;

Minion::Minion(string name, string description, int cost, int owner,
               Game* game, int atk, int def, int actions,
               shared_ptr<ActivatedAbility> activatedAbility, shared_ptr<TriggeredAbility> triggeredAbility, string type)
    : Card{name, description, type, cost, owner, game}, atk{atk}, def{def}, actions{actions}, activatedAbility{activatedAbility}, triggeredAbility{triggeredAbility} {}

bool Minion::activate() {
    if (!activatedAbility) return false;
    return activatedAbility->activate();
}

bool Minion::activate(int player, int minion) {
    if (!activatedAbility) return false;
    return activatedAbility->activate(player, minion);
}

void Minion::attachAbilities() {
    if (!triggeredAbility) return;
    game->getTrigger(triggeredAbility->getTriggerType()).attach(triggeredAbility);
    cout << "DEBUG: Ritual: attached trigger." << endl;
}
void Minion::detachAbilities() {
    if (!triggeredAbility) return;
    game->getTrigger(triggeredAbility->getTriggerType()).detach(triggeredAbility);
}

void Minion::attack() {
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
    consumeAction();
}

void Minion::attack(int target, std::shared_ptr<Minion> self) {
    if (getActions() == 0) {
        cout << "DEBUG: (Minion) " << name << " is out of actions." << endl;
        return;
    }
    game->battleMinion(self, target);
    consumeAction();
}

// TODO: investigate why shared_from_this() causes segfault. maybe something to do with dependency?
// void Minion::attack(int target) {
//     if (actions == 0) {
//         cout << "DEBUG: (Minion) " << name << "is out of actions." << endl;
//         return;
//     }
//     auto attackingMinion = shared_from_this();
//     game->battleMinion(attackingMinion, target);
//     --actions;
// }

void Minion::restoreAction() {
    actions = 1;
}
void Minion::consumeAction() {
    actions--;
}

void Minion::takeDamage(int dmg) {
    def -= dmg;
    if (def <= 0) {  // or is it better to put it outside of minion
        // game->getTrigger(Trigger::TriggerType::MinionExit).notifyObservers();
        //  could be easier to just have the minion itself call put to graveyard methods
        game->getTrigger(Trigger::TriggerType::MinionExit).notifyObservers();
        
    }
}

string Minion::getName() const {
    return name;
}

string Minion::getDesc() const {
    return description;
}

string Minion::getType() const {
    return type;
}

int Minion::getCost() const {
    return cost;
}
int Minion::getAttack() const {
    return atk;
}
int Minion::getDefence() const {
    return def;
}
int Minion::getActions() const {
    return actions;
}
shared_ptr<ActivatedAbility> Minion::getActivatedAbility() const {
    return activatedAbility;
}
shared_ptr<TriggeredAbility> Minion::getTriggeredAbility() const {
    return triggeredAbility;
}
void Minion::setDefence(int def) {
    this->def = def;
}
void Minion::setAttack(int atk) {
    this->atk = atk;
}

// Specific Minions
AirElemental::AirElemental(int owner, Game* game) : Minion{"Air Elemental", "", 0, owner, game, 1, 1, 0, nullptr, nullptr} {}
EarthElemental::EarthElemental(int owner, Game* game) : Minion{"Earth Elemental", "", 3, owner, game, 4, 4, 0, nullptr, nullptr} {}
BoneGolem::BoneGolem(int owner, Game* game) : Minion{"Bone Golem", "", 2, owner, game, 1, 3, 0, nullptr, make_shared<OnExitGainBuff>(game, owner)} {}
FireElemental::FireElemental(int owner, Game* game) : Minion{"Fire Elemental", "", 2, owner, game, 2, 2, 0, nullptr, make_shared<OnEnterDamage>(game, owner)} {}
PotionSeller::PotionSeller(int owner, Game* game) : Minion{"Potion Seller", "", 2, owner, game, 1, 3, 0, nullptr, make_shared<OnTurnEndBuff>(game, owner)} {}
NovicePyromancer::NovicePyromancer(int owner, Game* game) : Minion{"Novice Pyromancer", "", 1, owner, game, 0, 1, 0, make_shared<DealDamage>(game), nullptr} {}
ApprenticeSummoner::ApprenticeSummoner(int owner, Game* game) : Minion{"Apprentice Summoner", "", 1, owner, game, 1, 1, 0, make_shared<SummonAirElemental>(game), nullptr} {}
MasterSummoner::MasterSummoner(int owner, Game* game) : Minion{"Master Summoner", "", 3, owner, game, 2, 3, 0, make_shared<SummonThreeAirElemental>(game), nullptr} {}