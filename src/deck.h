#ifndef DECK_H
#define DECK_H

#include <fstream>
#include <memory>
#include <vector>
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
    void reSeed();
};

#endif
