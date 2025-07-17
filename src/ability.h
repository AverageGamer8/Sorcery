#ifndef ABILITY_H
#define ABILITY_H

#include <string>

class Ability {
public:
  std::string description;
  // TODO: card

  virtual void activate() = 0;
};

#endif