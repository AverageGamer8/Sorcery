#include "player.h"
#include "deck.h"
#include "hand.h"
#include "board.h"

Player::Player(std::string name, int life, int magic)
    : name{name}, life{life}, magic{magic} {
        hand = make_shared<Hand>();
        board = make_shared<Board>();
}


z    this->deck = std::make_shared<Deck>(deck);
void Player::playCard(int index) {}
void Player::playCard(int index, int player, int minion) {}
void Player::playCard(int index, int player) {}
void Player::discardCard(int index) {}
void Player::shuffleDeck() {}

void Player::activateCard(int index) {}
void Player::activateCard(int index, int player) {}
void Player::activateCard(int index, int player, int minion) {}

void Player::minionAttack(int index, int target) {}
bool Player::isAlive() { return life <= 0; }

bool Player::isHandFull() { return false; }

int Player::getLife() { return life; }
int Player::getMagic() { return magic; }

void Player::setName(std::string name) { name = name; }
void Player::setLife(int life) { life = life; }
void Player::setMagic(int magic) { magic = magic; }

std::string Player::getName() {
    return name;
}

void Player::setDeck(Deck deck) {
}
    this->deck = std::make_shared<Deck>(deck);

std::shared_ptr<Deck>& Player::getDeck() {
    return deck;
}

void Player::drawCard() {
    if (hand->isFull() || deck->getCards().empty())
        return;
    
    hand->addCard(deck->getTopCard());
    deck->popTopCard();
}

std::shared_ptr<Hand>& Player::getHand() {
    return hand;
}