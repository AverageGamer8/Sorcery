#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "board.h"
#include "deck.h"
#include "hand.h"
#include "../cards/minion.h"
#include "graveyard.h"
#include "../trigger.h"
#include "../triggeredability.h"

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
    map<Trigger::TriggerType, vector<shared_ptr<TriggeredAbility>>> triggers;


    bool hasMagicCost(int cost) const;

   public:
    Player(string name, int life, int magic);

    // ================== Gameplay =========================
    bool playCard(int index);
    bool playCard(int index, int player, int minion);
    bool playCard(int index, int player);

    void drawCard();
    void discardCard(int index);
    void shuffleDeck();

    bool activateCard(int index);
    bool activateCard(int index, int player);
    bool activateCard(int index, int player, int minion);

    void minionAttack(int index); // minion v player
    void minionAttack(int index, int target); // minion v minion
    bool isAlive();
    bool isHandFull();  // TODO PUT IN HAND class
    bool hasRitual() const;
    bool isGraveyardEmpty() const;

    void addTrigger(Trigger::TriggerType type, shared_ptr<>)

    // ================== Getters and Setters =====================
    const string getName() const;
    const int getLife() const;
    const int getMagic() const;
    const shared_ptr<Deck>& getDeck() const;
    const shared_ptr<Hand>& getHand() const;
    const shared_ptr<Board>& getBoard() const;
    const shared_ptr<Graveyard>& getGraveyard() const;
    const vector<shared_ptr<Minion>>& getMinions() const;
    const map<Trigger::TriggerType, vector<shared_ptr<TriggeredAbility>>>& getTriggers(Trigger::TriggerType type) const;

    void setName(string name);
    void setLife(int life);
    void setMagic(int magic);
    void setDeck(shared_ptr<Deck> deck);
};

#endif