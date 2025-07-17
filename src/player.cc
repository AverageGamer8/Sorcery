#include "player.h"
#include "deck.h"

Player::Player(std::string name, int life, int magic)
    : name{name}, life{life}, magic{magic} {}

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
    if (hand.size() >= 5 || deck->getCards().empty())
        return;
    
    hand.emplace_back(deck->getCards().back());
    deck->getCards().pop_back();
}

std::vector<shared_ptr<Card>>& Player::getHand() {
    return hand;
}