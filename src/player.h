#ifndef PLAYER_H
#define PLAYER_H

#include "minion.h"
#include "deck.h"
#include <memory>
#include <string>
#include <vector>

class Player {
  std::string name;
  int life;
  int magic;
  // TODO: add more fields.
  std::vector<std::unique_ptr<Minion>> minions;
  std::vector<shared_ptr<Card>> hand;
  std::shared_ptr<Deck> deck;

  friend class Minion;

public:
    Player(std::string name, int life, int magic);
    std::string getName();
    void setDeck(Deck deck);
    std::shared_ptr<Deck>& getDeck();
    void draw();
    std::vector<shared_ptr<Card>>& getHand();
};

#endif