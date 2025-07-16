#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <memory>
#include <vector>
class Player;

class Game {
  std::vector<std::unique_ptr<Player>> players;
  int activePlayer;

public:
  Game(std::vector<std::unique_ptr<Player>> players);
  Player *getPlayer(int index);
  Player *getActivePlayer();
  
  void startTurn(); // TODO
  void endTurn();
  int getWinner();
};

#endif