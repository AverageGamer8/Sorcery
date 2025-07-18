#ifndef PLAYER_H
#define PLAYER_H

#include "minion.h"
#include "deck.h"
#include "hand.h"
#include "board.h"
#include <memory>
#include <string>
#include <vector>

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
    std::string getName();
    void setDeck(Deck deck);
    std::shared_ptr<Deck>& getDeck();
    void draw();
    std::shared_ptr<Hand>& getHand();
};

#endif