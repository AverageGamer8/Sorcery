#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
using namespace std;

class Player;
class Trigger;

class Game {
    vector<unique_ptr<Player>> players;
    int activePlayer;
    Trigger turnStart;
    Trigger turnEnd;
    Trigger minionEnter;
    Trigger minionExit;

    public:
        Game(unique_ptr<Player> p1, unique_ptr<Player> p2);

        void startTurn();
        void endTurn();

        int getActivePlayerIndex();
        int getInactivePlayerIndex();
        unique_ptr<Player> getPlayer(int index);
}

#endif
