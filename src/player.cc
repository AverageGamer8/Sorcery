#include "player.h"

Player::Player(std::string name, int life, int magic)
    : name{name}, life{life}, magic{magic} {}

void Player::playCard(int index) {}
void Player::playCard(int index, int player, int minion) {}
void Player::playCard(int index, int player) {}

void Player::drawCard() {}
void Player::discardCard(int index) {}
void Player::shuffleDeck() {}

void Player::activateCard(int index) {}
void Player::activateCard(int index, int player) {}
void Player::activateCard(int index, int player, int minion) {}

void Player::minionAttack(int index, int target) {}
bool Player::isAlive() { return life <= 0; }

bool Player::isHandFull() { return false; }

std::string Player::getName() { return name; }
int Player::getLife() { return life; }
int Player::getMagic() { return magic; }

void Player::setName(std::string name) { name = name; }
void Player::setLife(int life) { life = life; }
void Player::setMagic(int magic) { magic = magic; }