#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include "player.h"
class Player;

class Game {
  std::vector<std::unique_ptr<Player>> players;
  int activePlayer;

public:
    Game(std::vector<std::unique_ptr<Player>> players);
    Player* getPlayer(int index);
    int getActiveIndex();
    int getInactiveIndex();

    void startTurn();
    void endTurn();
};

#endif