#ifndef GRAVEYARD_H
#define GRAVEYARD_H

#include "../cards/minion.h"
#include <vector>
#include <memory>
using namespace std;

class Graveyard {
    vector<shared_ptr<Minion>> minions;

    public:
        void addMinion(shared_ptr<Minion> m);
        shared_ptr<Minion> popTopMinion();
        vector<shared_ptr<Minion>>& getMinions();
        bool isEmpty();
};

#endif