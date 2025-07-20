#include <iostream> // TODO: remove debugs later.
#include "player.h"
#include "graveyard.h"

using namespace std;

Player::Player(string name, int life, int magic)
    : name{name}, life{life}, magic{magic} {
    hand = make_shared<Hand>();
    minions = make_shared<Board>(nullptr);
    graveyard = make_shared<Graveyard>();
}

void Player::playCard(int index) {}
void Player::playCard(int index, int player, int minion) {}
void Player::playCard(int index, int player) {}
void Player::discardCard(int index) {}
void Player::shuffleDeck() {}

void Player::drawCard() {
    if (hand->isFull() || deck->getCards().empty())
        return;
    hand->addCard(deck->popTopCard());

    hand->debugPrintHand(); // debug msg.
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
const shared_ptr<Board>& Player::getBoard() const { return minions; }
const shared_ptr<Graveyard>& Player::getGraveyard() const { return graveyard; }

void Player::setName(string name) { name = name; }
void Player::setLife(int life) { life = life; }
void Player::setMagic(int magic) { magic = magic; }
void Player::setDeck(shared_ptr<Deck> deck) {
    this->deck = deck;
}
