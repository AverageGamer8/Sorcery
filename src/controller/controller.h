#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <vector>

#include "../gameModel/game.h"
#include "../view/viewer.h"

class Controller {
    std::shared_ptr<Game> game;
    std::shared_ptr<Viewer> viewer;

   public:
    Controller(std::shared_ptr<Game> game, std::shared_ptr<Viewer> viewer);

    void end();
    void draw();
    void discard(int card);
    void attack(int attackingMinion);
    void attack(int attackingMinion, int receivingMinion);
    void play(int card);
    void play(int card, int onPlayer, int minion);
    void use(int minion);
    void use(int activeMinion, int onPlayer, int receivingMinion);

    // ======================= Display Controls ====================

    void help();
    void describe(int minion);
    void hand();
    void board();
};

#endif