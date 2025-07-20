#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include "../trigger.h"
#include "player.h"

class Player;

class Game {
    std::vector<std::shared_ptr<Player>> players;
    int activePlayer;

    Trigger turnStart;
    Trigger turnEnd;
    Trigger minionEnter;
    Trigger minionExit;

   public:
    Game(std::vector<std::shared_ptr<Player>> players);

    void setActivePlayer(int player);

    void battleMinion(int atk, int receivingMinion);

    void startTurn();  // TODO actual game handling
    void endTurn();
    // void addMinion();  // should we have it in player or game? easy to trigger in game.
    // void destroyMinion();

    int getWinner();

    Trigger &getTrigger(Trigger::TriggerType type);
    std::shared_ptr<Player> getPlayer(int index);
    std::shared_ptr<Player> getActivePlayer();
    shared_ptr<Player> getInactivePlayer();
    int getInactiveIndex();
    int getActiveIndex();
};

#endif