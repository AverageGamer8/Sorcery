#include "triggeredability.h"

#include <memory>

#include "../../gameModel/game.h"
#include "../../narrator.h"

using namespace std;

void TriggeredAbility::notify() {
    if (!shouldTrigger()) return;
    if (!activate()) {
        Narrator::announce("The ritual has run out of charges. It no longer activates.");
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
    Narrator::announce(p->getName() + "'s Dark Magic ritual activates with the new turn, granting them 1 magic.");

    auto ritual = p->getBoard()->getRitual();
    if (ritual && ritual->getCharges() < ritual->getActivationCost()) {
        Narrator::announce(p->getName() + "'s  Dark Magic ritual lies exhausted, its strength consumed.");
        return false;
    }
    p->setMagic(p->getMagic() + 1);
    ritual->setCharges(ritual->getCharges() - ritual->getActivationCost());
    return true;
}
bool OnStartGainMagic::shouldTrigger() const {
    return game->getActiveIndex() == player;
}

OnEnterBuff::OnEnterBuff(Game* game, int player) : TriggeredAbility{game, player, "Whenever a minion enters play under your control, it gains +1/+1", Trigger::TriggerType::MinionEnter} {}
bool OnEnterBuff::activate() {
    auto p = game->getPlayer(player);
    Narrator::announce(p->getName() + "'s Aura of Power ritual has activated.");

    auto ritual = p->getBoard()->getRitual();
    if (ritual && ritual->getCharges() < ritual->getActivationCost()) {
        Narrator::announce(p->getName() + "'s  Aura of Power ritual lies exhausted, its strength consumed.");
        return false;
    }
    // buff new minion
    auto& minions = p->getBoard()->getMinions();
    if (minions.empty()) return true;
    auto minion = minions.back();
    minion->setDefence(minion->getDefence() + 1);
    minion->setAttack(minion->getAttack() + 1);
    Narrator::announce(p->getName() + "'s Aura of Power ritual, has buffed their " + minion->getName() + " by +1/+1.");
    ritual->setCharges(ritual->getCharges() - ritual->getActivationCost());
    return true;
}
bool OnEnterBuff::shouldTrigger() const {
    return game->getActiveIndex() == player;
}

OnEnterDestroy::OnEnterDestroy(Game* game, int player) : TriggeredAbility{game, player, "Whenever a minion enters play, destroy it", Trigger::TriggerType::MinionEnter} {}
bool OnEnterDestroy::activate() {
    auto p = game->getPlayer(player);
    Narrator::announce(p->getName() + "'s Standstill ritual has activated.");

    auto ritual = p->getBoard()->getRitual();
    if (ritual && ritual->getCharges() < ritual->getActivationCost()) {
        Narrator::announce(p->getName() + "'s  Standstill ritual lies exhausted, its strength consumed.");
        return false;
    }
    if (!ritual) return true;
    // destroy added minion.
    auto activePlayer = game->getActivePlayer();
    auto& minions = activePlayer->getBoard()->getMinions();
    if (minions.empty()) return true;
    auto newMinion = minions.back();
    game->notifyTrigger(Trigger::TriggerType::MinionExit);
    activePlayer->getBoard()->removeMinion(minions.size() - 1);
    ritual->setCharges(ritual->getCharges() - ritual->getActivationCost());
    Narrator::announce(activePlayer->getName() + "'s Standstill ritual activates, destroying the newly summoned " + newMinion->getName() + ".");
    return true;
}
bool OnEnterDestroy::shouldTrigger() const {
    return true;
}

// ================== Minion Abilities =====================

OnExitGainBuff::OnExitGainBuff(Game* game, int player) : TriggeredAbility{game, player, "Gain +1/+1 whenever a minion leaves play.", Trigger::TriggerType::MinionExit} {}
bool OnExitGainBuff::activate() {
    auto p = game->getPlayer(player);
    for (auto& m : p->getBoard()->getMinions()) {
        if (m->getName() == "Bone Golem") {
            m->increaseDef(1);
            m->increaseAtk(1);
            Narrator::announce(p->getName() + "'s Bone Golem gains +1/+1 from the fallen.");
        }
    }
    return true;
}
bool OnExitGainBuff::shouldTrigger() const {
    return true;
}

OnEnterDamage::OnEnterDamage(Game* game, int player) : TriggeredAbility{game, player, "Whenever an opponents's minion enters play, deal 1 damage to it.", Trigger::TriggerType::MinionEnter} {}
bool OnEnterDamage::activate() {
    auto p = game->getActivePlayer();
    auto board = p->getBoard();
    if (board->getMinions().empty()) return true;
    auto minion = board->getMinion(board->getMinions().size() - 1);
    Narrator::announce(p->getName() + "'s " + minion->getName() + " takes 1 damage from Fire Elemental's burn.");
    if (minion->takeDamage(1)) {
        game->handleMinionDeath(game->getActiveIndex(), board->getMinions().size() - 1);
    }
    return true;
}
bool OnEnterDamage::shouldTrigger() const {
    return game->getActiveIndex() != player;
}
OnTurnEndBuff::OnTurnEndBuff(Game* game, int player) : TriggeredAbility{game, player, "At the end of your turn, all you minions gain +0/+1.", Trigger::TriggerType::TurnEnd} {}
bool OnTurnEndBuff::activate() {
    auto p = game->getPlayer(player);
    Narrator::announce(p->getName() + "'s Potion Seller grants +0/+1 to all their minions.");
    auto minions = p->getBoard()->getMinions();
    for (auto& m : minions) {
        m->increaseDef(1);
    }
    return true;
}
bool OnTurnEndBuff::shouldTrigger() const {
    return game->getActiveIndex() == player;
}
