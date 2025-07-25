#include "player.h"

#include <iostream>  // TODO: remove debugs later.

#include "../cards/enchantment.h"
#include "../cards/spell.h"  // TODO: investigate includes for this. should it have it?
#include "../narrator.h"

using namespace std;

Player::Player(string name, int life, int magic)
    : name{name}, life{life}, magic{magic} {
    hand = make_shared<Hand>();
    board = make_shared<Board>(nullptr);
    graveyard = make_shared<Graveyard>();
}

bool Player::hasMagicCost(int cost) const { return magic >= cost; }

// =============== Gameplay ===============
bool Player::playCard(int index, bool testingEnabled) {
    auto card = hand->getCardAtIndex(index);
    int cost = card->getCost();

    if (!hasMagicCost(cost)) {
        if (!testingEnabled) {
            // TODO: exception: not enough magic.
            cerr << "DEBUG: (Player) Does not have enough magic to use the card." << endl;
            return false;
        } else {
            setMagic(0);
        }
    }
    if (card->getType() == "Minion") {
        auto minion = static_pointer_cast<Minion>(card);
        Narrator::announce(name + " summons the minion '" + minion->getName() + "' (cost: " + to_string(minion->getCost()) + ").");
        board->addMinion(minion);
    } else if (card->getType() == "Spell") {
        auto spell = static_pointer_cast<Spell>(card);
        Narrator::announce(name + " casts the spell '" + spell->getName() + "' (cost: " + to_string(spell->getCost()) + ").");
        if (!spell->expend()) return false;
    } else if (card->getType() == "Ritual") {
        auto ritual = static_pointer_cast<Ritual>(card);
        Narrator::announce(name + " activates the ritual '" + ritual->getName() + "' (cost: " + to_string(ritual->getCost()) + ").");
        board->addRitual(ritual);
    } else {
        cerr << "DEBUG: (Player) Unrecognised card type. Only Minion, Spell. Ritual allowed" << endl;
        // TODO: exception. unrecognised card. Only minion,spell,ritual allowed.
    }

    if (hasMagicCost(cost) || !testingEnabled) {
        setMagic(getMagic() - cost);
    }
    hand->discardCard(index);
    return true;
}

bool Player::playCard(int index, int player, int minion, bool testingEnabled) {
    auto card = hand->getCardAtIndex(index);
    int cost = card->getCost();

    if (!hasMagicCost(cost)) {
        if (!testingEnabled) {
            // TODO: exception: not enough magic.
            cerr << "DEBUG: (Player) Does not have enough magic to use the card." << endl;
            return false;
        } else {
            setMagic(0);
        }
    }

    if (card->getType() == "Spell") {
        auto spell = static_pointer_cast<Spell>(card);
        Narrator::announce(name + " casts the spell '" + spell->getName() + "' (cost: " + to_string(spell->getCost()) + ").");
        if (!spell->expend(player, minion)) return false;
    } else if (card->getType() == "Enchantment") {
        auto ench = static_pointer_cast<Enchantment>(card);
        Narrator::announce(name + " enchants '" + ench->getName() + "' (cost: " + to_string(ench->getCost()) + ").");
        if (!ench->attach(player, minion)) {
            cerr << "No minion to enchant." << endl;
            return false;
        }
        Narrator::announce(ench->getName() + " has been enchanted.");
    } else {
        // todo exception, not found.
    }
    if (hasMagicCost(cost) || !testingEnabled) {
        setMagic(getMagic() - cost);
    }
    hand->discardCard(index);
    return true;
}
bool Player::playCard(int index, int player, bool testingEnabled) {  // Explicitly for using spell on a ritual
    auto card = hand->getCardAtIndex(index);
    int cost = card->getCost();

    if (!hasMagicCost(cost)) {
        if (!testingEnabled) {
            // TODO: exception: not enough magic.
            cerr << "DEBUG: (Player) Does not have enough magic to use the card." << endl;
            return false;
        } else {
            setMagic(0);
        }
    }

    auto spell = static_pointer_cast<Spell>(card);
    Narrator::announce(name + " casts the spell '" + spell->getName() + "' (cost: " + to_string(spell->getCost()) + ").");
    if (!spell->expend(player)) {
        cerr << "Spell cast failed." << endl;
        return false;
    }

    if (hasMagicCost(cost) || !testingEnabled) {
        setMagic(getMagic() - cost);
    }
    hand->discardCard(index);
    return true;
}
void Player::discardCard(int index) { hand->discardCard(index); }
void Player::shuffleDeck() { deck->shuffleDeck(); }

void Player::drawCard() {
    if (isHandFull()) return;
    auto card = deck->popTopCard();
    if (!card) {
        cerr << "DEBUG: Player: Deck is out of cards." << endl;
        return;
    }
    hand->addCard(card);
}

bool Player::activateCard(int index, bool testingEnabled) {
    auto m = getBoard()->getMinion(index);
    auto ability = m->getActivatedAbility();
    int cost = m->getActivateCost();
    if (!(m->getActivatedAbility())) {
        // TODO: no activated ability
        cerr << "DEBUG: (Player) Minion does not have activated ability." << endl;
        return false;
    }
    if (!hasMagicCost(cost)) {
        if (!testingEnabled) {
            // TODO: exception: not enough magic.
            cerr << "DEBUG: (Player) Does not have enough magic to use the card." << endl;
            return false;
        } else {
            setMagic(0);
        }
    }
    if (m->getActions() < 1) {
        // TODO: exception not enough magic.
        cerr << "DEBUG: (Player) Minion has no actions left." << endl;
        return false;
    }
    Narrator::announce(name + "'s minion '" + m->getName() + "' unleashes its ability (cost: " + to_string(m->getActivateCost()) + ").");
    if (!m->activate()) return false;
    if (hasMagicCost(cost) || !testingEnabled) {
        setMagic(getMagic() - cost);
    }
    m->consumeAction();
    return true;
}

bool Player::activateCard(int index, int player, int minion, bool testingEnabled) {
    auto m = getBoard()->getMinion(index);
    auto ability = m->getActivatedAbility();
    int cost = m->getActivateCost();

    if (!ability) {
        // TODO: no activated ability
        cerr << "DEBUG: (Player) Minion does not have activated ability." << endl;
        return false;
    }
    if (!hasMagicCost(cost)) {
        if (!testingEnabled) {
            // TODO: exception: not enough magic.
            cerr << "DEBUG: (Player) Does not have enough magic to use the card." << endl;
            return false;
        } else {
            setMagic(0);
        }
    }

    if (m->getActions() < 1) {
        // TODO: exception not enough magic.
        cerr << "DEBUG: (Player) Minion has no actions left." << endl;
        return false;
    }
    Narrator::announce(name + "'s minion '" + m->getName() + "' unleashes its ability (cost: " + to_string(m->getActivateCost()) + ").");
    if (!m->activate(player, minion)) return false;
    if (hasMagicCost(cost) || !testingEnabled) {
        setMagic(getMagic() - cost);
    }
    m->consumeAction();
    return true;
}

void Player::minionAttack(int index) {  // attacks player
    auto minion = board->getMinion(index);
    if (!minion) {
        cerr << "DEBUG: Player: index out of bounds of board." << endl;
        return;
    }
    minion->attack();
}

void Player::minionAttack(int index, int target) {
    auto minion = board->getMinion(index);
    if (!minion) {
        cerr << "DEBUG: Player: index out of bounds of board." << endl;
        return;
    }
    minion->attack(target); 
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
