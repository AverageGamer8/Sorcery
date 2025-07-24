#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "ascii_graphics.h"
#include "display.h"

using namespace std;

class Minion;
class Enchantment;
class Ritual;
class Spell;

class TextDisplay : public sorcDisplay {
    ostream& out;
    bool enablePrintDelay = false;

    void printCardTemplate(const card_template_t& cardInfo);
    card_template_t getMinionInfo(shared_ptr<Minion> minion) const;
    card_template_t getEnchantmentInfo(shared_ptr<Enchantment> ench) const;
    card_template_t getRitualInfo(shared_ptr<Ritual> ritual) const;
    card_template_t getSpellInfo(shared_ptr<Spell> spell) const;
    void printTemplatesRow(vector<card_template_t> cardTemplates) const;
    card_template_t getCardInfo(shared_ptr<Card> card) const;
    vector<card_template_t> getBoardMinionsRow(shared_ptr<Player> player);
    vector<card_template_t> getBoardPlayerRow(shared_ptr<Player> player);
    void printHorizontalBorder() const;
    card_template_t buildVerticalCardBorder() const;

   public:
    TextDisplay(std::ostream& out, bool enablePrintDelay);
    void printHelp() override;
    void printDescribe(Game* game, int minion) override;
    void printHand(Game* game) override;
    void printBoard(Game* game) override;
};

#endif