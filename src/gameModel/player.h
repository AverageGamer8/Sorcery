#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../cards/minion.h"
#include "board.h"
#include "deck.h"
#include "graveyard.h"
#include "hand.h"

using namespace std;

class Player {
    string name;
    int life;
    int magic;

    shared_ptr<Hand> hand;
    shared_ptr<Deck> deck;
    shared_ptr<Board> board;
    shared_ptr<Graveyard> graveyard;

    bool hasMagicCost(int cost) const;

   public:
    Player(string name, int life, int magic);

    // ================== Gameplay =========================
    bool playCard(int index, bool testingEnabled);
    bool playCard(int index, int player, int minion, bool testingEnabled);
    bool playCard(int index, int player, bool testingEnabled);

    void drawCard();
    void discardCard(int index);
    void shuffleDeck();

    bool activateCard(int index, bool testingEnabled);
    bool activateCard(int index, int player, int minion, bool testingEnabled);

    void minionAttack(int index);              // minion vs. player
    void minionAttack(int index, int target);  // minion vs. minion
    bool isAlive();
    bool isHandFull();
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
    const vector<shared_ptr<Minion>>& getMinions() const;

    void setName(string name);
    void setLife(int life);
    void setMagic(int magic);
    void setDeck(shared_ptr<Deck> deck);
};

#endif