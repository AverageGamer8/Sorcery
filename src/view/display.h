#ifndef DISPLAY_H
#define DISPLAY_H

#include <memory>

#include "../gameModel/game.h"

class sorcDisplay {
   public:
    // TODO: use NVI
    virtual void printGame(std::shared_ptr<Game> game) = 0;
    virtual void printHelp() = 0;  // Give a list a commands
    virtual void printDescribe(std::shared_ptr<Game> game, int minion) = 0;
    virtual void printHand(std::shared_ptr<Game> game) = 0;
    virtual void printBoard(std::shared_ptr<Game> game) = 0;
};

#endif