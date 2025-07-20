#ifndef DECK_H
#define DECK_H

#include <memory>
#include <vector>
#include <fstream>
using namespace std;

class Card;
class Game;

class Deck {
    int owner;
    vector<shared_ptr<Card>> cards;
    long long seed;

    public:
        Deck(int player);
        void loadDeck(ifstream& inf, shared_ptr<Game> game);
        void shuffleDeck();
        vector<shared_ptr<Card>>& getCards();
        shared_ptr<Card> popTopCard();
};

#endif
