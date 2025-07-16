#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"
#include <memory>

class Display {
    public:
        virtual void printGame(std::shared_ptr<Game> game);
        virtual void printHelp(); // Give a list a commands
};

#endif