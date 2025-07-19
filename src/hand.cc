#include "hand.h"
using namespace std;

vector<shared_ptr<Card>>& Hand::getCards() {
    return cards;
}

bool Hand::isFull() {
    return cards.size() >= MAX_HAND_SIZE;
}

void Hand::addCard(shared_ptr<Card> card) {
    cards.emplace_back(card);
}
