#include "game.h"

#include <iostream>  // for DEBUG not needed later
Game::Game(std::vector<std::shared_ptr<Player>> players)
    : players{players} {}

void Game::startTurn() {
    std::cout << "DEBUG (Game): Player " << activePlayer << " starts their turn."
              << std::endl;
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
    turnStart.notifyObservers();
}
void Game::endTurn() {
    std::cout << "DEBUG (Game): Player " << activePlayer << " ends their turn."
              << std::endl;
    turnEnd.notifyObservers();
    activePlayer = (activePlayer == 0) ? 1 : 0;  // swap turn
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
        opp->getBoard()->removeMinion(receivingMinion);
        opp->getGraveyard()->addMinion(oppMinion);
        minionExit.notifyObservers();
    }
    attackingMinion->takeDamage(oppMinion->getAttack());
    if (attackingMinion->getDefence() <= 0) {
        int attackerIndex = attacker->getBoard()->getMinionIndex(attackingMinion);
        attacker->getBoard()->removeMinion(attackerIndex);
        attacker->getGraveyard()->addMinion(attackingMinion);
        minionExit.notifyObservers();
    }

    cout << "DEBUG: Game: Battle Results\n"
         << "  Attacker: " << attackingMinion->getName()
         << " (ATK: " << attackingMinion->getAttack() << ", DEF: " << attackingMinion->getDefence() << ")\n"
         << "  Defender: " << oppMinion->getName()
         << " (ATK: " << oppMinion->getAttack() << ", DEF: " << oppMinion->getDefence() << ")\n";
}

bool Game::playCard(int card) {  // Wrapper to notify MinionEnter observers
    auto player = getActivePlayer();
    auto cardPtr = player->getHand()->getCardAtIndex(card);
    if (!player->playCard(card)) return false;
    if (cardPtr->getType() == "Minion") {
        minionEnter.notifyObservers();
    }
    return true;
}

void Game::setActivePlayer(int player) { activePlayer = player; }
void Game::setWinner(int winner) { winningPlayer = winner; }
int Game::getWinner() const { return winningPlayer; }  // TODO

shared_ptr<Player> Game::getPlayer(int index) { return players[index]; }
shared_ptr<Player> Game::getActivePlayer() { return getPlayer(activePlayer); }
shared_ptr<Player> Game::getInactivePlayer() { return getPlayer(getInactiveIndex()); }

int Game::getInactiveIndex() {
    return (activePlayer + 1) % 2;
}

int Game::getActiveIndex() {
    return activePlayer;
}

Trigger &Game::getTrigger(Trigger::TriggerType type) {  // easier to call, could also use 4 getters as well.
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
            std::cerr << "Game::getTrigger: invalid type." << std::endl;
    }
}

void Game::notifyTrigger(Trigger::TriggerType type) {
    auto activePlayer = getActivePlayer();
    auto inactivePlayer = getInactivePlayer();

    for (auto& trigger : )
}
