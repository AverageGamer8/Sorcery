#ifndef DISPLAY_H
#define DISPLAY_H

#include <memory>

#include "../gameModel/game.h"

class sorcDisplay {
   public:
    // TODO: use NVI
    virtual void printHelp() = 0;  // Give a list a commands
    virtual void printDescribe(Game* game, int minion) = 0;
    virtual void printHand(Game* game) = 0;
    virtual void printBoard(Game* game) = 0;

    virtual ~sorcDisplay() = default;
};

#endif