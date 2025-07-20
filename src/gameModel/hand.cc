#include "hand.h"

#include <iostream>  // TODO: Remove deubgs

using namespace std;

void Hand::debugPrintHand() {  // debug function.
    for (auto& c : cards) {
        cout << "DEBUG: (Hand) CARD - " << c->getName() << endl;
    }
}

bool Hand::isFull() {
    return cards.size() >= MAX_HAND_SIZE;
}

void Hand::addCard(shared_ptr<Card> card) {
    if (isFull()) return;
    cards.emplace_back(card);
}

void Hand::discardCard(int index) {
    if (index >= cards.size()) {
        cout << "DEBUG: (Hand) Can't discard, out of range." << endl;
        return;
    }
    cards.erase(cards.begin() + index);
}

// ============== getters & setters ==========

vector<shared_ptr<Card>>& Hand::getCards() { return cards; }
int Hand::getSize() const { return cards.size(); }
shared_ptr<Card> Hand::getCardAtIndex(int index) const {
    if (index < 0 || index >= getSize()) {
        throw out_of_range("Hand::getCardAtIndex - index out of range");
    }
    return cards[index];
}
int Hand::getIndexOfCard(shared_ptr<Card> card) const {
    for (int i = 0; i < cards.size(); i++) {
        if (cards[i] == card) return i;
    }
    throw invalid_argument("Hand::getIndexOfCard - Card not found in hand.");
}
