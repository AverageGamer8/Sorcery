#include "player.h"

#include "board.h"
#include "deck.h"
#include "hand.h"
using namespace std;

Player::Player(string name, int life, int magic)
    : name{name}, life{life}, magic{magic} {
    hand = make_shared<Hand>();
    board = make_shared<Board>();
}

void Player::playCard(int index) {}
void Player::playCard(int index, int player, int minion) {}
void Player::playCard(int index, int player) {}
void Player::discardCard(int index) {}
void Player::shuffleDeck() {}

void Player::drawCard() {
    if (hand->isFull() || deck->getCards().empty())
        return;

    hand->addCard(deck->getTopCard());
    deck->popTopCard();
}
void Player::activateCard(int index) {}
void Player::activateCard(int index, int player) {}
void Player::activateCard(int index, int player, int minion) {}

void Player::minionAttack(int index, int target) {}

bool Player::isAlive() { return life <= 0; }
bool Player::isHandFull() { return hand->isFull(); }

const string Player::getName() const { return name; }
const int Player::getLife() const { return life; }
const int Player::getMagic() const { return magic; }
const shared_ptr<Deck>& Player::getDeck() const { return deck; }
const shared_ptr<Hand>& Player::getHand() const { return hand; }
const vector<unique_ptr<Minion>>& Player::getMinions() const{ return minions; }

void Player::setName(string name) { name = name; }
void Player::setLife(int life) { life = life; }
void Player::setMagic(int magic) { magic = magic; }
void Player::setDeck(Deck deck) {
    this->deck = make_shared<Deck>(deck);
}
