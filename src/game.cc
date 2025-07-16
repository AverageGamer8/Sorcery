#include "game.h"

Game::Game(std::vector<std::unique_ptr<Player>> players)
    : players{std::move(players)} {}

Player *Game::getPlayer(int index) { return players[index].get(); }