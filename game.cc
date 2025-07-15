#include "game.h"
#include "player.h"
using namespace std;

Game::Game(unique_ptr<Player> p1, unique_ptr<Player> p2) {
    players.emplace_back(p1);
    players.emplace_back(p2);
}
