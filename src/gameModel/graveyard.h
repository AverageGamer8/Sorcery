#ifndef GRAVEYARD_H
#define GRAVEYARD_H

#include <memory>
#include <vector>

#include "../cards/enchantment.h"
#include "../cards/minion.h"
using namespace std;

class Graveyard {
    vector<shared_ptr<Minion>> minions;

   public:
    void addMinion(shared_ptr<Minion> m);
    shared_ptr<Minion> getTopMinion();
    shared_ptr<Minion> popTopMinion();
    vector<shared_ptr<Minion>>& getMinions();
    bool isEmpty();
};

#endif
