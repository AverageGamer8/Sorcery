#ifndef DISPLAY_H
#define DISPLAY_H

#include <memory>

#include "game.h"

class Display {
   public:
    // TODO: use NVI
    virtual void printGame(std::shared_ptr<Game> game) = 0;
    virtual void printHelp() = 0;  // Give a list a commands
};

#endif