#include "game.h"

Game::Game(std::vector<std::unique_ptr<Player>> players) : players{std::move(players)} {}

Player* Game::getPlayer(int index) {
    return players[index].get();
}

int Game::getActiveIndex() {
    return activePlayer;
}

int Game::getInactiveIndex() {
    return (activePlayer + 1) % 2;
}
