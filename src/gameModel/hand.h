#ifndef HAND_H
#define HAND_H

#include <fstream>
#include <memory>
#include <vector>

#include "../cards/card.h"
using namespace std;

const int MAX_HAND_SIZE = 5;

class Hand {
    int owner;
    vector<shared_ptr<Card>> cards;

   public:
    vector<shared_ptr<Card>>& getCards();
    bool isFull();
    void addCard(shared_ptr<Card> card);
    void discardCard(int index);

    int getSize() const;
    shared_ptr<Card> getCardAtIndex(int index) const;
    int getIndexOfCard(shared_ptr<Card> card) const;
};

#endif