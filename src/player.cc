#include "player.h"
#include "deck.h"
#include "hand.h"
#include "board.h"

Player::Player(std::string name, int life, int magic)
    : name{name}, life{life}, magic{magic} {
        hand = make_shared<Hand>();
        board = make_shared<Board>();
}

std::string Player::getName() {
    return name;
}

void Player::setDeck(Deck deck) {
    this->deck = std::make_shared<Deck>(deck);
}

std::shared_ptr<Deck>& Player::getDeck() {
    return deck;
}

void Player::draw() {
    if (hand->isFull() || deck->getCards().empty())
        return;
    
    hand->addCard(deck->getTopCard());
    deck->popTopCard();
}

std::shared_ptr<Hand>& Player::getHand() {
    return hand;
}