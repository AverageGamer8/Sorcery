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

    auto ritual = p->getBoard()->getRitual();
    if (ritual && ritual->getCharges() < ritual->getActivationCost()) {
        Narrator::announce(p->getName() + "'s  Dark Magic ritual lies exhausted, its strength consumed.");
        return false;
    }
    if (!ritual) return true;
    Narrator::announce(p->getName() + "'s Dark Magic ritual activates with the new turn, granting them 1 magic.");
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

    auto ritual = p->getBoard()->getRitual();
    if (ritual && ritual->getCharges() < ritual->getActivationCost()) {
        Narrator::announce(p->getName() + "'s  Aura of Power ritual lies exhausted, its strength consumed.");
        return false;
    }
    if (!ritual) return true;
    // buff new minion
    auto& minions = p->getBoard()->getMinions();
    if (minions.empty()) return true;
    Narrator::announce(p->getName() + "'s Aura of Power ritual has activated.");
    auto minion = minions.back();
    minion->increaseAtk(1);
    minion->increaseDef(1);
    Narrator::announce(p->getName() + "'s Aura of Power ritual has buffed their " + minion->getName() + " by +1/+1.");
    ritual->setCharges(ritual->getCharges() - ritual->getActivationCost());
    return true;
}
bool OnEnterBuff::shouldTrigger() const {
    return game->getActiveIndex() == player;
}

OnEnterDestroy::OnEnterDestroy(Game* game, int player) : TriggeredAbility{game, player, "Whenever a minion enters play, destroy it", Trigger::TriggerType::MinionEnter} {}
bool OnEnterDestroy::activate() {
    auto p = game->getPlayer(player);
    
    auto ritual = p->getBoard()->getRitual();
    if (ritual && ritual->getCharges() < ritual->getActivationCost()) {
        Narrator::announce(p->getName() + "'s  Standstill ritual lies exhausted, its strength consumed.");
        return false;
    }
    if (!ritual) return true;
    // destroy added minion.
    auto activePlayer = game->getActivePlayer();
    auto& minions = activePlayer->getBoard()->getMinions();
    Narrator::announce(p->getName() + "'s Standstill ritual has activated.");
    auto newMinion = minions.back();
    game->notifyTrigger(Trigger::TriggerType::MinionExit);
    activePlayer->getBoard()->removeMinion(activePlayer->getBoard()->getMostRecent());
    ritual->setCharges(ritual->getCharges() - ritual->getActivationCost());
    Narrator::announce(p->getName() + "'s Standstill ritual destroys the newly summoned " + newMinion->getName() + ".");
    return true;
}
bool OnEnterDestroy::shouldTrigger() const {
    auto board = game->getActivePlayer()->getBoard();
    return board->getMostRecent() < board->getMinions().size();
}

// ================== Minion Abilities =====================

OnExitGainBuff::OnExitGainBuff(Game* game, int player) : TriggeredAbility{game, player, "Gain +1/+1 whenever a minion leaves play.", Trigger::TriggerType::MinionExit} {}
bool OnExitGainBuff::activate() {
    auto p = game->getPlayer(player);
    for (auto& m : p->getBoard()->getMinions()) {
        if (m->getName() == "Bone Golem") {
            m->increaseAtk(1);
            m->increaseDef(1);
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
    auto minion = board->getMinion(board->getMostRecent());
    Narrator::announce(p->getName() + "'s " + minion->getName() + " is burned by " + game->getPlayer(player)->getName() + "'s Fire Elemental.");
    if (minion->takeDamage(1)) {
        game->handleMinionDeath(game->getActiveIndex(), board->getMinions().size() - 1);
    }
    return true;
}
bool OnEnterDamage::shouldTrigger() const {
    auto board = game->getActivePlayer()->getBoard();
    return game->getActiveIndex() != player && board->getMostRecent() < board->getMinions().size();
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
