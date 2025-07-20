#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <iostream>
#include <memory>
#include <vector>

#include "ascii_graphics.h"
#include "display.h"

using namespace std;

class TextDisplay : public Display {
    ostream& out;

    void printCardTemplate(const card_template_t& cardInfo);
    void printTemplatesRow(vector<card_template_t> cardTemplates) const;
    card_template_t getCardInfo(shared_ptr<Card> card) const;
    vector<card_template_t> getBoardMinionsRow(shared_ptr<Player> player);
    vector<card_template_t> getBoardPlayerRow(shared_ptr<Player> player);
    void printHorizontalBorder() const;
    card_template_t buildVerticalCardBorder() const;

   public:
    TextDisplay(std::ostream& out);
    void printGame(shared_ptr<Game> game) override;
    void printHelp() override;
    void printDescribe(shared_ptr<Game> game, int minion) override;
    void printHand(shared_ptr<Game> game) override;
    void printBoard(shared_ptr<Game> game) override;
};

#endif