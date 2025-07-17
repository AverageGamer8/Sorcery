#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "trigger.h"
#include <memory>
#include <vector>

class Player;

class Game {
  std::vector<std::unique_ptr<Player>> players;
  int activePlayer;

  Trigger turnStart;
  Trigger turnEnd;
  Trigger minionEnter;
  Trigger minionExit;

public:
  Game(std::vector<std::unique_ptr<Player>> players);
  Player *getPlayer(int index);
  Player *getActivePlayer();

  void setActivePlayer(int player);

  void startTurn(); // TODO actual game handling
  void endTurn();
  void addMinion(); // should we have it in player or game? easy to trigger in game.
  void destroyMinion();

  int getWinner();

  Trigger& getTrigger(Trigger::TriggerType type); 
};

#endif