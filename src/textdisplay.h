#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "display.h"
#include <iostream>
#include <memory>

class TextDisplay : public Display {
    std::ostream& out;
public:
    TextDisplay(std::ostream& out);
    void printGame(std::shared_ptr<Game> game) override;
    void printHelp() override;
};

#endif