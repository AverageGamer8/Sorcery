/*
THIS IS AN EXAMPLE USAGE. DELETE IN SUBMISSION!
*/

#ifndef CONCRETEABILITY_H
#define CONCRETEABILITY_H

#include "triggeredability.h"
#include <iostream>

class ConcreteAbility : public TriggeredAbility {
  int ownerPlayerId;

public:
  ConcreteAbility(Game* game, int ownerPlayerId)
    : TriggeredAbility(game), ownerPlayerId(ownerPlayerId) {}

  void activate() override {
    std::cout << "DEBUG: Triggered - ConcreteAbility! Hello from Player " << ownerPlayerId << std::endl;
  }
};

#endif