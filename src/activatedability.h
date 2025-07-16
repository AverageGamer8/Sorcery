#ifndef ACTIVATEDABILITY_H
#define ACTIVATEDABILITY_H

#include "ability.h"

class ActivatedAbility : public Ability {
public:
  int cost;
  void activate() override;
};

#endif