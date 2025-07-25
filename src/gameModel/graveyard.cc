#include "graveyard.h"
using namespace std;

void Graveyard::addMinion(shared_ptr<Minion> m) {
    minions.emplace_back(m);
}
shared_ptr<Minion> Graveyard::getTopMinion() {
    return minions.back();
}
shared_ptr<Minion> Graveyard::popTopMinion() {
    auto minion = getTopMinion();
    minions.pop_back();
    return minion;
}

vector<shared_ptr<Minion>>& Graveyard::getMinions() {
    return minions;
}

bool Graveyard::isEmpty() {
    return minions.empty();
}
