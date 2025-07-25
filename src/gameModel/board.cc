#include "board.h"

#include <memory>
#include <vector>

#include "../argexception.h"
#include "../cards/enchantment.h"
using namespace std;

bool Board::isFull() const {
    return minions.size() >= MAX_BOARD_SIZE;
}

bool Board::hasRitual() const {
    return ritual != nullptr;
}

void Board::addRitual(shared_ptr<Ritual> r) {
    if (!r) return;
    ritual = r;
}

void Board::addMinion(shared_ptr<Minion> m) {
    if (isFull() || !m) {
        return;
    }
    minions.emplace_back(m);
    mostRecent = minions.size() - 1;
}

shared_ptr<Minion> Board::removeMinion(int target) {
    int size = minions.size();
    if (target >= size) return nullptr;
    auto minion = getMinion(target);
    minions.erase(minions.begin() + target);
    while (minion->getType() == "Enchantment") {
        auto ench = static_pointer_cast<Enchantment>(minion);
        minion = ench->getMinion();
    }
    return minion;
}

void Board::removeRitual() { ritual = nullptr; }


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

    throw ArgException("Attacking minion's index not found.");
}

size_t Board::getMostRecent() const {
    return mostRecent;
}

shared_ptr<Ritual> Board::getRitual() { return ritual; }

void Board::setRitual(shared_ptr<Ritual> ritual) {
    this->ritual = ritual;
}

void Board::setMinion(int i, shared_ptr<Minion> m) {
    if (i >= minions.size()) return;
    minions[i] = m;
}
