#ifndef ABILITY_H
#define ABILITY_H

#include <string>

class Ability {
  std::string description;
  // TODO: card

public:
  virtual void activate();
};

#endif