#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

class Player {
  std::string name;
  int life;
  int magic;
  // TODO: add more fields.

public:
  Player(std::string name, int life, int magic);
  std::string getName();
};

#endif