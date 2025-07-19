#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>
#include <vector>

#include "board.h"
#include "deck.h"
#include "hand.h"
#include "../cards/minion.h"
#include "graveyard.h"

using namespace std;

class Player {
    string name;
    int life;
    int magic;
    // TODO: add more fields.
    shared_ptr<Hand> hand;
    shared_ptr<Deck> deck;
    shared_ptr<Board> board;
    shared_ptr<Graveyard> graveyard;

    friend class Minion;

    bool hasMagicCost(int cost) const;

   public:
    Player(string name, int life, int magic);

    // ================== Gameplay =========================
    void playCard(int index);
    void playCard(int index, int player, int minion);
    void playCard(int index, int player);

    void drawCard();
    void discardCard(int index);
    void shuffleDeck();

    void activateCard(int index);
    void activateCard(int index, int player);
    void activateCard(int index, int player, int minion);

    void minionAttack(int index, int target);
    bool isAlive();
    bool isHandFull();  // TODO PUT IN HAND class
    bool hasRitual() const;
    bool isGraveyardEmpty() const;

    // ================== Getters and Setters =====================
    const string getName() const;
    const int getLife() const;
    const int getMagic() const;
    const shared_ptr<Deck>& getDeck() const;
    const shared_ptr<Hand>& getHand() const;
    const shared_ptr<Board>& getBoard() const;
    const shared_ptr<Graveyard>& getGraveyard() const;
    const vector<unique_ptr<Minion>>& getMinions() const;

    void setName(string name);
    void setLife(int life);
    void setMagic(int magic);
    void setDeck(shared_ptr<Deck> deck);
};

#endif