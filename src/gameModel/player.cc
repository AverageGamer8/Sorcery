#include "player.h"

#include <iostream>  // TODO: remove debugs later.

#include "../cards/spell.h"  // TODO: investigate includes for this. should it have it?

using namespace std;

Player::Player(string name, int life, int magic)
    : name{name}, life{life}, magic{magic} {
    hand = make_shared<Hand>();
    board = make_shared<Board>();
}

bool Player::hasMagicCost(int cost) const { return magic >= cost; }

// =============== Gameplay ===============
void Player::playCard(int index) {
    auto card = hand->getCardAtIndex(index);
    int cost = card->getCost();

    if (!hasMagicCost(cost)) {  // TODO: testing allows you to use spell,activate without magic, set to 0.
        // TODO: exception: not enough magic.
    }
    if (card->getType() == "Minion") {
        auto minion = static_pointer_cast<Minion>(card);
        board->addMinion(minion);
    } else if (card->getType() == "Spell") {
        auto spell = static_pointer_cast<Spell>(card);
        // TODO: Call spell->expend.
    } else if (card->getType() == "Ritual") {
        // TODO ritual.
    } else {
        // TODO: exception. unrecognised card. Only minion,spell,ritual allowed.
    }
    setMagic(getMagic() - cost);
    hand->discardCard(index);
}
void Player::playCard(int index, int player, int minion) {
    auto card = hand->getCardAtIndex(index);
    int cost = card->getCost();
    if (!hasMagicCost(cost)) {
        // TODO: exception not enough magic.
    }
    cout << "DEBUG: player: playcard has enough magic!" << endl;
    if (card->getType() == "Spell") {
        auto spell = static_pointer_cast<Spell>(card);
        // TODO: expend spell.

    } else if (card->getType() == "Enchantment") {
        // todo enchantments.
    } else {
        // todo exception, not found.
    }
    setMagic(getMagic() - cost);
    hand->discardCard(index);
}
void Player::playCard(int index, int player) {}
void Player::discardCard(int index) { hand->discardCard(index); }
void Player::shuffleDeck() { deck->shuffleDeck(); }

void Player::drawCard() {
    hand->addCard(deck->getTopCard());
    deck->popTopCard();

    hand->debugPrintHand();  // debug msg.
}
void Player::activateCard(int index) {}
void Player::activateCard(int index, int player) {}
void Player::activateCard(int index, int player, int minion) {}

void Player::minionAttack(int index, int target) {}

bool Player::isAlive() { return life <= 0; }
bool Player::isHandFull() { return hand->isFull(); }
bool Player::hasRitual() const {
    //  return !(ritual == nullptr);  //TODO ritual.
    return false;
}
bool Player::isGraveyardEmpty() const {
    // TODO graveyard
    return false;
}

// =============== Getters and Setters ==============

const string Player::getName() const { return name; }
const int Player::getLife() const { return life; }
const int Player::getMagic() const { return magic; }
const shared_ptr<Deck>& Player::getDeck() const { return deck; }
const shared_ptr<Hand>& Player::getHand() const { return hand; }
const vector<unique_ptr<Minion>>& Player::getMinions() const { return minions; }

void Player::setName(string name) { name = name; }
void Player::setLife(int life) { life = life; }
void Player::setMagic(int magic) { magic = magic; }
void Player::setDeck(shared_ptr<Deck> deck) { this->deck = deck; }
