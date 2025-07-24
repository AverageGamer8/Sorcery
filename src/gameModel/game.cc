#include "game.h"

#include <iostream>  // for DEBUG not needed later

using namespace std;

Game::Game(vector<shared_ptr<Player>> players)
    : players{players} {}

void Game::startTurn() {
    cout << "DEBUG (Game): Player " << activePlayer << " starts their turn."
         << endl;
    auto player = getActivePlayer();

    // Replenish magic and minion actions
    player->setMagic(player->getMagic() + 1);  // Gains 1 magic.

    auto hand = player->getHand();
    auto board = player->getBoard();
    for (auto card : hand->getCards()) {
        if (card->getType() == "Minion") {
            auto minion = static_pointer_cast<Minion>(card);
            minion->restoreAction();
        }
    }
    for (auto minion : board->getMinions()) {
        minion->restoreAction();
    }

    player->drawCard();
    notifyTrigger(Trigger::TriggerType::TurnStart);
}

void Game::endTurn() {
    std::cout << "DEBUG (Game): Player " << activePlayer << " ends their turn."
              << std::endl;
    notifyTrigger(Trigger::TriggerType::TurnEnd);
    activePlayer = (activePlayer == 0) ? 1 : 0;  // swap turn
}

void Game::handleMinionDeath(int player, int minion) {
    auto p = getPlayer(player);
    auto m = p->getBoard()->getMinion(minion);
    p->getBoard()->removeMinion(minion);
    p->getGraveyard()->addMinion(m);
}

void Game::battleMinion(shared_ptr<Minion> attackingMinion, int receivingMinion) {
    auto attacker = getActivePlayer();
    auto opp = getInactivePlayer();
    auto oppMinion = opp->getBoard()->getMinion(receivingMinion);
    cout << "DEBUG: Game: Minion Battle\n"
         << "  Attacker: " << attackingMinion->getName()
         << " (ATK: " << attackingMinion->getAttack() << ", DEF: " << attackingMinion->getDefence() << ")\n"
         << "  Defender: " << oppMinion->getName()
         << " (ATK: " << oppMinion->getAttack() << ", DEF: " << oppMinion->getDefence() << ")\n";

    oppMinion->takeDamage(attackingMinion->getAttack());
    if (oppMinion->getDefence() <= 0) {
        handleMinionDeath(getInactiveIndex(), receivingMinion);
    }
    attackingMinion->takeDamage(oppMinion->getAttack());
    if (attackingMinion->getDefence() <= 0) {
        int attackerIndex = attacker->getBoard()->getMinionIndex(attackingMinion);
        handleMinionDeath(getActiveIndex(), attackerIndex);
    }

    cout << "DEBUG: Game: Battle Results\n"
         << "  Attacker: " << attackingMinion->getName()
         << " (ATK: " << attackingMinion->getAttack() << ", DEF: " << attackingMinion->getDefence() << ")\n"
         << "  Defender: " << oppMinion->getName()
         << " (ATK: " << oppMinion->getAttack() << ", DEF: " << oppMinion->getDefence() << ")\n";
}

bool Game::playCard(int card, bool testingEnabled) {  // Wrapper to notify MinionEnter observers
    auto player = getActivePlayer();
    auto cardPtr = player->getHand()->getCardAtIndex(card);
    if (!player->playCard(card, testingEnabled)) return false;
    if (cardPtr->getType() == "Minion") {
        notifyTrigger(Trigger::TriggerType::MinionEnter);
    }
    return true;
}

void Game::setActivePlayer(int player) { activePlayer = player; }
void Game::setWinner(int winner) { winningPlayer = winner; }
int Game::getWinner() const { return winningPlayer; }

shared_ptr<Player> Game::getPlayer(int index) { return players[index]; }
shared_ptr<Player> Game::getActivePlayer() { return getPlayer(activePlayer); }
shared_ptr<Player> Game::getInactivePlayer() { return getPlayer(getInactiveIndex()); }

int Game::getInactiveIndex() {
    return (activePlayer + 1) % 2;
}

int Game::getActiveIndex() {
    return activePlayer;
}

Trigger &Game::getTrigger(Trigger::TriggerType type) {
    switch (type) {
        case Trigger::TriggerType::TurnStart:
            return turnStart;
        case Trigger::TriggerType::TurnEnd:
            return turnEnd;
        case Trigger::TriggerType::MinionEnter:
            return minionEnter;
        case Trigger::TriggerType::MinionExit:
            return minionExit;
        default:
            cerr << "Game::getTrigger: Invalid type." << endl;
    }
}

void Game::notifyTrigger(Trigger::TriggerType type) {
    auto activePlayer = getActivePlayer();
    auto inactivePlayer = getInactivePlayer();

    for (auto& minion : activePlayer->getBoard()->getMinions()) {
        if (minion->getTriggeredAbility() && minion->getTriggeredAbility()->getTriggerType() == type) {
            minion->getTriggeredAbility()->notify();
        }
    }
    if (activePlayer->hasRitual() && activePlayer->getBoard()->getRitual()->getTriggeredAbility()->getTriggerType() == type) {
        activePlayer->getBoard()->getRitual()->getTriggeredAbility()->notify();
    }

    for (auto& minion : inactivePlayer->getBoard()->getMinions()) {
        if (minion->getTriggeredAbility() && minion->getTriggeredAbility()->getTriggerType() == type) {
            minion->getTriggeredAbility()->notify();
        }
    }
    if (inactivePlayer->hasRitual() && inactivePlayer->getBoard()->getRitual()->getTriggeredAbility()->getTriggerType() == type) {
        inactivePlayer->getBoard()->getRitual()->getTriggeredAbility()->notify();
    }
}
