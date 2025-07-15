#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

class Player;

class Game {
  std::vector<std::unique_ptr<Player *>> players;

public:
    Game();

    playCard(int index);
    playCard(int index, int player);
    playCard(int index, int player, int minion);
};