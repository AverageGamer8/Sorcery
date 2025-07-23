#include "triggeredability.h"

#include <iostream>  // TODO: remove debugs
#include <memory>

#include "./gameModel/game.h"

using namespace std;

void TriggeredAbility::notify() {
    if (!shouldTrigger()) return;
    if (!activate()) {
        cout << "DEBUG: (TriggeredAbility) No more charges. Removed ritual" << endl;
    }
}

Trigger::TriggerType TriggeredAbility::getTriggerType() const {
    return type;
}

// ================== Ritual Abilities ===================
// Note: activate returns false when out of charges.

OnStartGainMagic::OnStartGainMagic(Game* game, int player) : TriggeredAbility{game, player, "At the start of your turn, gain 1 magic", Trigger::TriggerType::TurnStart} {}
bool OnStartGainMagic::activate() {  // gains 1 magic at start of turn.
    auto p = game->getPlayer(player);
    cout << "DEBUG: TriggeredAbility) OnStartGainMagic: activated " << endl;

    auto ritual = p->getBoard()->getRitual();
    if (ritual && ritual->getCharges() <= 0) {
        p->getBoard()->removeRitual();
        return false;
    }
    p->setMagic(p->getMagic() + 1);
    ritual->setCharges(ritual->getCharges() - 1);
    return true;
}
bool OnStartGainMagic::shouldTrigger() const {
    return game->getActiveIndex() == player;
}

OnEnterBuff::OnEnterBuff(shared_ptr<Game> game, int player) : TriggeredAbility{game, player, "Whenever a minion enters play under your control, it gains +1/+1", Trigger::TriggerType::MinionEnter} {}
bool OnEnterBuff::activate() {
    auto p = game->getPlayer(player);
    cout << "DEBUG: (TriggeredAbility) OnEnterBuff: activated " << endl;

    auto ritual = p->getBoard()->getRitual();
    if (ritual && ritual->getCharges() <= 0) {
        p->getBoard()->removeRitual();
        return false;
    }
    // buff new minion
    auto& minions = p->getBoard()->getMinions();
    if (minions.empty()) return true;
    auto minion = minions.back();
    minion->setDefence(minion->getDefence() + 1);
    minion->setAttack(minion->getAttack() + 1);
    cout << "DEBUG: (TriggeredAbility) OnEnterBuff: Buffed newly entered minion +1/+1" << endl;
    ritual->setCharges(ritual->getCharges() - 1);
    return true;
}
bool OnEnterBuff::shouldTrigger() const {
    return true;
}

OnEnterDestroy::OnEnterDestroy(shared_ptr<Game> game, int player) : TriggeredAbility{game, player, "Whenever a minion enters play, destroy it", Trigger::TriggerType::MinionEnter} {}
bool OnEnterDestroy::activate() {
    auto p = game->getPlayer(player);
    cout << "DEBUG: (TriggeredAbility) OnEnterDestroy: activated " << endl;

    auto ritual = p->getBoard()->getRitual();
    if (ritual && ritual->getCharges() <= 0) {
        p->getBoard()->removeRitual();
        return false;
    }
    if (!ritual) return true;
    // destroy added minion.
    auto activePlayer = game->getActivePlayer();
    auto& minions = activePlayer->getBoard()->getMinions();
    if (minions.empty()) return true;
    auto newMinion = minions.back();
    activePlayer->getGraveyard()->addMinion(newMinion);
    activePlayer->getBoard()->removeMinion(minions.size() - 1);
    ritual->setCharges(ritual->getCharges() - 1);
    cout << "DEBUG: (TriggeredAbility) OnEnterDestroy: Destroyed newly entered minion, sent to graveyard." << endl;
    return true;
}
bool OnEnterDestroy::shouldTrigger() const {
    return true;
}

// ================== Minion Abilities =====================

OnExitGainBuff::OnExitGainBuff(shared_ptr<Game> game, int player) : TriggeredAbility{game, player, "Gain +1/+1 whenever a minion leaves play.", Trigger::TriggerType::MinionExit} {}
bool OnExitGainBuff::activate() {
    auto p = game->getPlayer(player);
    cout << "DEBUG: (TriggeredAbility) OnExitGainBuff: activated " << endl;
    for (auto& m : p->getBoard()->getMinions()) {
        if (m->getName() == "Bone Golem") {
            m->setDefence(m->getDefence() + 1);
            m->setAttack(m->getAttack() + 1);
        }
    }
    return true;
}
bool OnExitGainBuff::shouldTrigger() const {
    return true;
}

OnEnterDamage::OnEnterDamage(shared_ptr<Game> game, int player) : TriggeredAbility{game, player, "Whenever an opponents's minion enters play, deal 1 damage to it.", Trigger::TriggerType::MinionEnter} {}
bool OnEnterDamage::activate() {
    cout << "DEBUG: (TriggeredAbility) OnEnterDamage: activated " << endl;
    auto p = game->getActivePlayer();
    auto board = p->getBoard();
    if (board->getMinions().empty()) return true;
    board->getMinion(board->getMinions().size() - 1)->takeDamage(1);
    return true;
}
bool OnEnterDamage::shouldTrigger() const {
    return true;
}
OnTurnEndBuff::OnTurnEndBuff(shared_ptr<Game> game, int player) : TriggeredAbility{game, player, "At the end of your turn, all you minions gain +0/+1.", Trigger::TriggerType::TurnEnd} {}
bool OnTurnEndBuff::activate() {
    cout << "DEBUG: (TriggeredAbility) OnTurnEndBuff: activated " << endl;
    auto p = game->getPlayer(player);
    auto minions = p->getBoard()->getMinions();
    for (auto& m : minions) {
        m->setDefence(m->getDefence() + 1);
    }
    return true;
}
bool OnTurnEndBuff::shouldTrigger() const {
    return game->getActiveIndex() == player;
}
