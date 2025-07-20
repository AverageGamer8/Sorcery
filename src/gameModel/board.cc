#include "board.h"

#include <memory>
#include <vector>
using namespace std;

bool Board::isFull() {
    return minions.size() >= MAX_BOARD_SIZE;
}

void Board::addMinion(std::shared_ptr<Minion> m) {
    if (!isFull())
        minions.emplace_back(m);
}

void Board::removeMinion(int target) {
    int size = minions.size();
    if (target >= size)
        return;

    minions.erase(minions.begin() + target);
}

vector<shared_ptr<Minion>>& Board::getMinions() {
    return minions;
}

shared_ptr<Minion> Board::getMinion(int index) {
    return minions[index];
}

void Board::setRitual(shared_ptr<Ritual> ritual) {
    this->ritual = ritual;
}
