#ifndef VIEWER_H
#define VIEWER_H

#include <memory>
#include <vector>

#include "../gameModel/game.h"
#include "display.h"

class Viewer {
    std::vector<std::shared_ptr<sorcDisplay>> displays;
    Game* game;

   public:
    enum Command {
        HELP,
        DESCRIBE,
        HAND,
        BOARD
    };
    Viewer(std::vector<std::shared_ptr<sorcDisplay>> displays,
           Game* game);
    void display(Command command);
    void display(Command command, int minion);
};

#endif
