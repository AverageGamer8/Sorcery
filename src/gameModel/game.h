#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include "../cards/abilities/trigger.h"
#include "../cards/abilities/triggeredability.h"
#include "player.h"

class Player;

class Game {
    std::vector<std::shared_ptr<Player>> players;
    int activePlayer;
    int winningPlayer = -1;

   public:
    Game(std::vector<std::shared_ptr<Player>> players);

    // ================== Gameplay =====================
    void setActivePlayer(int player);

    void handleMinionDeath(int player, int minion);
    void battleMinion(shared_ptr<Minion> attackingMinion, int receivingMinion);
    bool playCard(int card, bool testingEnabled);

    void startTurn();
    void endTurn();

    // ============ Getters and Setters =====================

    std::shared_ptr<Player> getPlayer(int index);
    std::shared_ptr<Player> getActivePlayer();
    shared_ptr<Player> getInactivePlayer();
    void setWinner(int winner);
    int getWinner() const;
    int getInactiveIndex();
    int getActiveIndex();

    void notifyTrigger(Trigger::TriggerType type);
};

#endif