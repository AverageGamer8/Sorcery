#ifndef PLAYER_H
#define PLAYER_H

#include "minion.h"
#include <memory>
#include <string>
#include <vector>

class Player {
  std::string name;
  int life;
  int magic;
  // TODO: add more fields.
  std::vector<std::unique_ptr<Minion>> minions;

  friend class Minion;

public:
  Player(std::string name, int life, int magic);
  std::string getName();

  void playCard(int index);
  void playCard(int index, int player, int minion);
  void playCard(int index, int player);

  void drawCard();
  void discardCard(int index);
  void shuffleDeck();

  void activateCard(int index);
  void activateCard(int index, int player);
  void activateCard(int index, int player, int minion);

  void minionAttack(int index, int target);
  bool isAlive();
  void endTurn();
};

#endif