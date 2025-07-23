#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <vector>

#include "../cards/minion.h"
#include "../cards/ritual.h"

using namespace std;

const int MAX_BOARD_SIZE = 5;

class Board {
    vector<shared_ptr<Minion>> minions;
    shared_ptr<Ritual> ritual;

   public:
    Board(shared_ptr<Ritual> ritual) : ritual{ritual} {}

    bool isFull() const;
    bool hasRitual() const;
    void addMinion(std::shared_ptr<Minion> m);
    void addRitual(std::shared_ptr<Ritual> r);
    void removeMinion(int target);
    void removeRitual();
    void setMinion(int i, std::shared_ptr<Minion> m);

    vector<shared_ptr<Minion>>& getMinions();
    shared_ptr<Minion> getMinion(int index);
    int getMinionIndex(shared_ptr<Minion> m) const;
    shared_ptr<Ritual> getRitual();
    void setRitual(shared_ptr<Ritual> ritual);
};

#endif
