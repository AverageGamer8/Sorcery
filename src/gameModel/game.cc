#include "game.h"

#include <iostream>  // for DEBUG not needed later
Game::Game(std::vector<std::shared_ptr<Player>> players)
    : players{players} {}

void Game::startTurn() {
    std::cout << "DEBUG (Game): Player " << activePlayer << " starts their turn."
              << std::endl;
    auto player = getActivePlayer();
    player->setMagic(player->getMagic() + 1);  // Gains 1 magic.

    if (!player->isHandFull()) {  // Draw a card, if not full.
        player->drawCard();
    }

    turnStart.notifyObservers();
}
void Game::endTurn() {
    std::cout << "DEBUG (Game): Player " << activePlayer << " ends their turn."
              << std::endl;
    turnEnd.notifyObservers();
    activePlayer = (activePlayer == 0) ? 1 : 0;  // swap turn
}

void Game::battleMinion(int atk, int receivingMinion) {
    shared_ptr<Player> opp = getInactivePlayer();
    shared_ptr<Minion> oppMinion = opp->getBoard()->getMinion(receivingMinion);
    cout << "DEBUG: Game: Attacking " << oppMinion->getName() << ". Their HP: " << oppMinion->getDefence() << endl;;
    oppMinion->setDefence(oppMinion->getDefence() - atk);
    if (oppMinion->getDefence() <= 0) {
        oppMinion->setDefence(0);
        opp->getBoard()->removeMinion(receivingMinion);
        opp->getGraveyard()->addMinion(oppMinion);
        minionExit.notifyObservers();
    }
    cout << "DEBUG: Game: After attack - Opponent: "  << oppMinion->getName() << ". HP: " << oppMinion->getDefence() << endl;
}

void Game::setActivePlayer(int player) { activePlayer = player; }
int Game::getWinner() { return -1; }  // TODO

shared_ptr<Player> Game::getPlayer(int index) { return players[index]; }
shared_ptr<Player> Game::getActivePlayer() { return getPlayer(activePlayer); }
shared_ptr<Player> Game::getInactivePlayer() {return getPlayer(getInactiveIndex());}

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