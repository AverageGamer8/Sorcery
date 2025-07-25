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
    size_t mostRecent = 0;

   public:
    Board(shared_ptr<Ritual> ritual) : ritual{ritual} {}

    bool isFull() const;
    bool hasRitual() const;
    void addMinion(shared_ptr<Minion> m);
    void addRitual(shared_ptr<Ritual> r);
    shared_ptr<Minion> removeMinion(int target);
    void removeRitual();

    vector<shared_ptr<Minion>>& getMinions();
    shared_ptr<Minion> getMinion(int index);
    int getMinionIndex(shared_ptr<Minion> m) const;
    size_t getMostRecent() const;
    shared_ptr<Ritual> getRitual();
    void setRitual(shared_ptr<Ritual> ritual);
    void setMinion(int i, shared_ptr<Minion> m);
};

#endif
