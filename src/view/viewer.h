#ifndef VIEWER_H
#define VIEWER_H

#include <memory>
#include <vector>

#include "display.h"
#include "../gameModel/game.h"

class Viewer {
    std::vector<std::shared_ptr<sorcDisplay>> displays;
    Game* game;

   public:
    enum Command {  // TODO: Add more enums with more controller commands
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
