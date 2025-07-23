#include "player.h"

#include <iostream>  // TODO: remove debugs later.

#include "../cards/spell.h"  // TODO: investigate includes for this. should it have it?
#include "../cards/enchantment.h"

using namespace std;

Player::Player(string name, int life, int magic)
    : name{name}, life{life}, magic{magic} {
    hand = make_shared<Hand>();
    board = make_shared<Board>(nullptr);
    graveyard = make_shared<Graveyard>();
}

bool Player::hasMagicCost(int cost) const { return magic >= cost; }

// =============== Gameplay ===============
bool Player::playCard(int index) {
    auto card = hand->getCardAtIndex(index);
    int cost = card->getCost();

    if (!hasMagicCost(cost)) {  // TODO: testing allows you to use spell,activate without magic, set to 0.
        // TODO: exception: not enough magic.
        cout << "DEBUG: (Player) Does not have enough magic to use the card." << endl;
        return false;
    }
    if (card->getType() == "Minion") {
        cout << "DEBUG: (Player) Played card is a Minion" << endl;
        auto minion = static_pointer_cast<Minion>(card);
        board->addMinion(minion);
    } else if (card->getType() == "Spell") {
        auto spell = static_pointer_cast<Spell>(card);
        if (!spell->expend()) return false;
    } else if (card->getType() == "Ritual") {
        auto ritual = static_pointer_cast<Ritual>(card);
        board->addRitual(ritual);
    } else {
        cout << "DEBUG: (Player) Unrecognised card type. Only Minion, Spell. Ritual allowed" << endl;
        // TODO: exception. unrecognised card. Only minion,spell,ritual allowed.
    }

    setMagic(getMagic() - cost);
    hand->discardCard(index);
    return true;
}

bool Player::playCard(int index, int player, int minion) {
    auto card = hand->getCardAtIndex(index);
    int cost = card->getCost();
    if (!hasMagicCost(cost)) {
        // TODO: exception not enough magic.
        cout << "DEBUG: (Player) Does not have enough magic to use the card." << endl;
        return false;
    }
    // cout << "DEBUG: player: playcard has enough magic!" << endl;
    if (card->getType() == "Spell") {
        auto spell = static_pointer_cast<Spell>(card);
        if (!spell->expend(player, minion)) return false;
    } else if (card->getType() == "Enchantment") {
        auto ench = static_pointer_cast<Enchantment>(card);
        if (!ench->attach(player, minion)) {
            cout << "No minion to enchant." << endl;
            return false;
        }
    } else {
        // todo exception, not found.
    }
    setMagic(getMagic() - cost);
    hand->discardCard(index);
    return true;
}
bool Player::playCard(int index, int player) {  // Ritual
    auto card = hand->getCardAtIndex(index);
    int cost = card->getCost();
    if (!hasMagicCost(cost)) {
        // TODO: exception not enough magic.
        cout << "DEBUG: (Player) Does not have enough magic to use the card." << endl;
        return false;
    }
    auto spell = static_pointer_cast<Spell>(card);
    if (!spell->expend(player)) return false;

    setMagic(getMagic() - cost);
    hand->discardCard(index);
    return true;
}
void Player::discardCard(int index) { hand->discardCard(index); }
void Player::shuffleDeck() { deck->shuffleDeck(); }

void Player::drawCard() {
    auto card = deck->popTopCard();
    if (!card) {
        cout << "DEBUG: Player: Deck is out of cards." << endl;
        return;
    }
    hand->addCard(card);
    deck->popTopCard();

    // hand->debugPrintHand();  // debug msg.
}
void Player::activateCard(int index) {}
void Player::activateCard(int index, int player) {}
void Player::activateCard(int index, int player, int minion) {}

void Player::minionAttack(int index) {  // attacks player
    auto minion = board->getMinion(index);
    if (!minion) {
        cout << "DEBUG: Player: index out of bounds of board." << endl;
        return;
    }
    minion->attack();
}
void Player::minionAttack(int index, int target) {
    auto minion = board->getMinion(index);
    if (!minion) {
        cout << "DEBUG: Player: index out of bounds of board." << endl;
        return;
    }

    minion->attack(target, minion);  // pass the shared_ptr
}

bool Player::isAlive() { return life <= 0; }
bool Player::isHandFull() { return hand->isFull(); }
bool Player::hasRitual() const { return getBoard()->hasRitual(); }
bool Player::isGraveyardEmpty() const { return graveyard->isEmpty(); }

// =============== Getters and Setters ==============

const string Player::getName() const { return name; }
const int Player::getLife() const { return life; }
const int Player::getMagic() const { return magic; }
const shared_ptr<Deck>& Player::getDeck() const { return deck; }
const shared_ptr<Hand>& Player::getHand() const { return hand; }
const shared_ptr<Board>& Player::getBoard() const { return board; }
const shared_ptr<Graveyard>& Player::getGraveyard() const { return graveyard; }
const vector<shared_ptr<Minion>>& Player::getMinions() const { return board->getMinions(); }

void Player::setName(string name) { this->name = name; }
void Player::setLife(int life) { this->life = life; }
void Player::setMagic(int magic) { this->magic = magic; }
void Player::setDeck(shared_ptr<Deck> deck) { this->deck = deck; }
