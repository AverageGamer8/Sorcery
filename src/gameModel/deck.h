#ifndef DECK_H
#define DECK_H

#include <fstream>
#include <memory>
#include <vector>
using namespace std;

class Card;
class Game;

class Deck {
    int owner;
    vector<shared_ptr<Card>> cards;
    long long seed;

   public:
    Deck(int player);
    void loadDeck(ifstream& inf, Game* game);
    void shuffleDeck();
    vector<shared_ptr<Card>>& getCards();
    shared_ptr<Card> popTopCard();
};

#endif
