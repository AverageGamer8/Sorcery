#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <iostream>
#include <memory>

#include "display.h"
#include "ascii_graphics.h"

using namespace std;

class TextDisplay : public Display {
    ostream& out;

    void printCardTemplate(const card_template_t& cardInfo);

   public:
    TextDisplay(std::ostream& out);
    void printGame(shared_ptr<Game> game) override;
    void printHelp() override;
    void printDescribe(shared_ptr<Game> game, int minion) override;
    void printHand(shared_ptr<Game> game) override;
    void printBoard(shared_ptr<Game> game) override;
};

#endif