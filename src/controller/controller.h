#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <vector>

#include "../gameModel/game.h"
#include "../view/viewer.h"

class Controller {
    Game* game;
    std::shared_ptr<Viewer> viewer;

   public:
    Controller(Game* game, std::shared_ptr<Viewer> viewer);

    void end();
    void draw();
    bool discard(int card);
    bool attack(int attackingMinion);
    bool attack(int attackingMinion, int receivingMinion);
    bool play(int card);
    bool play(int card, int onPlayer, int minion);
    bool use(int minion);
    bool use(int activeMinion, int onPlayer, int receivingMinion);

    // ======================= Display Controls ====================

    void help();
    bool describe(int minion);
    void hand();
    void board();
};

#endif