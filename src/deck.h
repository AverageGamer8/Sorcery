#ifndef DECK_H
#define DECK_H

#include <memory>
#include <vector>
#include <fstream>
using namespace std;

class Card;

class Deck {
    int owner;
    vector<unique_ptr<Card>> cards;
    long long seed;

    public:
        Deck(int player);
        void loadDeck(ifstream& inf);
        void shuffleDeck();
        vector<unique_ptr<Card>>& getCards();
};

#endif
