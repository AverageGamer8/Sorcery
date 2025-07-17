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
};

#endif