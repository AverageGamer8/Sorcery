#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include <iostream>
#include <memory>
#include <vector>

#include "window.h"
#include "display.h"
#include "../cards/card.h"
#include "../cards/minion.h"
#include "../cards/enchantment.h"
#include "../cards/ritual.h"
#include "../cards/spell.h"

using namespace std;

class GraphicsDisplay : public sorcDisplay {
    Xwindow xw;
    int width, height, cWidth, cHeight;

    void drawDesc(int x, int y, string desc);
    void printMinion(int x, int y, shared_ptr<Minion> minion);
    void printEnchantment(int x, int y, shared_ptr<Enchantment> ench);
    void printRitual(int x, int y, shared_ptr<Ritual> ritual);
    void printSpell(int x, int y, shared_ptr<Spell> spell);
    void printSorcery(int x, int y);
    void printPlayer(int pos, shared_ptr<Player> player);

   public:
    GraphicsDisplay(int width = 960, int length = 720);
    void printGame(shared_ptr<Game> game) override;
    void printHelp() override;
    void printDescribe(shared_ptr<Game> game, int minion) override;
    void printHand(shared_ptr<Game> game) override;
    void printBoard(shared_ptr<Game> game) override;
};

#endif