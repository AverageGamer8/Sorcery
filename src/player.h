#ifndef PLAYER_H
#define PLAYER_H

#include "minion.h"
#include "deck.h"
#include "hand.h"
#include "board.h"
#include <memory>
#include <string>
#include <vector>

#include "minion.h"

class Player {
  std::string name;
  int life;
  int magic;
  // TODO: add more fields.
  std::vector<std::unique_ptr<Minion>> minions;
  std::shared_ptr<Hand> hand;
  std::shared_ptr<Deck> deck;
  std::shared_ptr<Board> board;

    friend class Minion;

   public:
    Player(std::string name, int life, int magic);

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
    bool isHandFull(); // TODO PUT IN HAND class

    // ================== Getters and Setters =====================
    std::string getName();
    int getLife();
    int getMagic();

    void setName(std::string name);
    void setLife(int life);
    void setMagic(int magic);
    void setDeck(Deck deck);
    std::shared_ptr<Deck>& getDeck();
    std::shared_ptr<Hand>& getHand();
};

#endif