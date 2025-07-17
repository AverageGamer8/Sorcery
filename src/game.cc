#include "game.h"
#include <iostream> // DEBUG not needed later
Game::Game(std::vector<std::unique_ptr<Player>> players)
    : players{std::move(players)} {}

void Game::startTurn() {
  std::cout << "DEBUG (Game): Player " << activePlayer << " starts their turn."
            << std::endl;
  turnStart.notifyObservers();
}
void Game::endTurn() {
  std::cout << "DEBUG (Game): Player " << activePlayer << " ends their turn."
            << std::endl;
  turnEnd.notifyObservers();
  activePlayer = (activePlayer == 0) ? 1 : 0; // swap turn
}

Player *Game::getPlayer(int index) { return players[index].get(); }

Player *Game::getActivePlayer() { return getPlayer(activePlayer); }

void Game::setActivePlayer(int player) { activePlayer = player; }
int Game::getWinner() { return -1; } // TODO

Trigger& Game::getTrigger(Trigger::TriggerType type) { // easier to call, could also use 4 getters as well.
  switch (type) {
    case Trigger::TriggerType::TurnStart: return turnStart;
    case Trigger::TriggerType::TurnEnd: return turnEnd;
    case Trigger::TriggerType::MinionEnter: return minionEnter;
    case Trigger::TriggerType::MinionExit: return minionExit;
    default: std::cerr << "Game::getTrigger: invalid type." << std::endl;
  }
}

int Game::getInactiveIndex() {
    return (activePlayer + 1) % 2;
}