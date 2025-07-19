#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include <iostream>
#include <memory>
#include <vector>

#include "window.h"
#include "display.h"

using namespace std;

class GraphicsDisplay : public Display {
    Xwindow xw;
    int width = 960, height = 600, cWidth = 160, cHeight = 120, 

    void printCardTemplate(const card_template_t& cardInfo);

   public:
    GraphicsDisplay(int width, int length);
    void printGame(shared_ptr<Game> game) override;
    void printHelp() override;
    void printDescribe(shared_ptr<Game> game, int minion) override;
    void printHand(shared_ptr<Game> game) override;
    void printBoard(shared_ptr<Game> game) override;
};

#endif