#ifndef DECK_H
#define DECK_H

#include <memory>
#include <vector>
#include <fstream>
using namespace std;

class Card;

class Deck {
    int player;
    vector<unique_ptr<Card>> cards;
    int seed;

    public:
        Deck(int player);
        void loadDeck(ifstream& inf);
        void shuffleDeck();
        void reSeed();
}

#endif
