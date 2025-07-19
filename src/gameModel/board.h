#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>

#include "../cards/minion.h"
using namespace std;

const int MAX_BOARD_SIZE = 5;

class Board {
    std::vector<std::shared_ptr<Minion>> minions;

   public:
    bool isFull();
    void addMinion(std::shared_ptr<Minion> m);
    void removeMinion(int target);
    vector<shared_ptr<Minion>>& getMinions();
};

#endif
