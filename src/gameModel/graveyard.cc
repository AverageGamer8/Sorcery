#include "graveyard.h"
using namespace std;

void Graveyard::addMinion(shared_ptr<Minion> m) {
    while (m->getType() == "Enchantment") {
        auto tmp = static_pointer_cast<Enchantment>(m);
        m = tmp->getMinion();
    }
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
