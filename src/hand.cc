#include "hand.h"

#include <iostream>  // TODO: Remove deubgs

using namespace std;

void Hand::debugPrintHand() {  // debug function.
    for (auto& c : cards) {
        cout << "DEBUG: (Hand) CARD - " << c->getName() << endl;
    }
}

vector<shared_ptr<Card>>& Hand::getCards() {
    return cards;
}

bool Hand::isFull() {
    return cards.size() >= MAX_HAND_SIZE;
}

void Hand::addCard(shared_ptr<Card> card) {
    cards.emplace_back(card);
}

int Hand::getSize() const { return cards.size(); }

shared_ptr<Card> Hand::getCardAtIndex(int index) const { return cards[index]; }