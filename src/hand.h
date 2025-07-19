#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <memory>
#include <vector>
#include <fstream>
using namespace std;

const int MAX_HAND_SIZE = 5;

class Hand {
    int owner;
    vector<shared_ptr<Card>> cards;

    public:
        vector<shared_ptr<Card>>& getCards();
        bool isFull();
        void addCard(shared_ptr<Card> card);
};


#endif