#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <iostream>
#include <memory>

#include "display.h"

class TextDisplay : public Display {
    std::ostream& out;

   public:
    TextDisplay(std::ostream& out);
    void printGame(std::shared_ptr<Game> game) override;
    void printHelp() override;
};

#endif