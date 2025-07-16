#include "player.h"

Player::Player(std::string name, int life, int magic)
    : name{name}, life{life}, magic{magic} {}

std::string Player::getName() { return name; }