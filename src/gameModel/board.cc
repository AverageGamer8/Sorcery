#include "board.h"

#include <memory>
#include <vector>
using namespace std;

bool Board::isFull() const {
    return minions.size() >= MAX_BOARD_SIZE;
}

bool Board::hasRitual() const {
    return ritual != nullptr;
}

void Board::addMinion(shared_ptr<Minion> m) {
    if (isFull() || !m) {
        return;
    }
    minions.emplace_back(m);
}

void Board::addRitual(shared_ptr<Ritual> r) {
    if (!r) return;
    if (hasRitual()) {
        ritual->detachAbilities();
    }
    ritual = r;
    ritual->attachAbilities();
}

void Board::removeMinion(int target) {
    int size = minions.size();
    if (target >= size)
        return;

    minions.erase(minions.begin() + target);
}

void Board::removeRitual() { ritual = nullptr; }

void Board::setMinion(int i, shared_ptr<Minion> m) {
    minions[i] = m;
}

vector<shared_ptr<Minion>>& Board::getMinions() {
    return minions;
}

shared_ptr<Minion> Board::getMinion(int index) {
    if (index >= minions.size()) return nullptr;
    return minions[index];
}

int Board::getMinionIndex(shared_ptr<Minion> m) const {
    for (int i = 0; i < minions.size(); ++i) {
        if (minions[i] == m) {
            return i;
        }
    }

    return -1;
    // TODO: exception.
}

shared_ptr<Ritual> Board::getRitual() { return ritual; }

void Board::setRitual(shared_ptr<Ritual> ritual) {
    this->ritual = ritual;
}
