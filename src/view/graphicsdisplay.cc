#include "graphicsdisplay.h"

#include "../cards/spell.h"  // TODO: investigate dependecny this shouldnt be needed
using namespace std;

// red: attack
// blue: defence, magic
// green: player life, ritual charges
const int ATK = Xwindow::Red;
const int DEF = Xwindow::Blue, MP = Xwindow::Blue;
const int LIFE = Xwindow::Green, COST = Xwindow::Green, CHARGE = Xwindow::Green;
const int BLANK = Xwindow::White;
const int EMPTY = Xwindow::Black;
const int offset = 10;

GraphicsDisplay::GraphicsDisplay(int width, int height) : 
    xw{width, height}, width{width}, height{height}, cWidth{width / 6}, cHeight{height / 5} { xw.fillRectangle(0, 0, width, height); }

void GraphicsDisplay::printCardTemplate(const card_template_t& cardInfo) {
    for (int i = 0; i < cardInfo.size(); ++i) {
        out << cardInfo[i];
        if (i < cardInfo.size() - 1) {
            out << endl;
        }
    }
}

void GraphicsDisplay::printPlayer(int pos, shared_ptr<Player> player) {
    int left = cWidth * 2, top = pos == 0 ? 0 : cHeight * 4;
    xw.fillRectangle(left, top, cWidth, cHeight, BLANK);
    xw.drawString(left + (cWidth * 0.4), top + (pos == 0 ? cHeight * 0.2 : cHeight * 0.6), player->getName());
    xw.fillRectangle(left, top + (pos == 0 ? cHeight * 0.8 : 0), cWidth * 0.2, cHeight * 0.2, LIFE);
    xw.drawString(left + offset, top + (pos == 0 ? cHeight * 0.8 : 0) + offset, to_string(player->getLife()));
    xw.fillRectangle(left + (cWidth * 0.8), top + (pos == 0 ? cHeight * 0.8 : 0), cWidth * 0.2, cHeight * 0.2, MP);
    xw.drawString(left + (cWidth * 0.8) + offset, top + (pos == 0 ? cHeight * 0.8 : 0) + offset, to_string(player->getMagic()));
}

void GraphicsDisplay::printMinion(int x, int y, shared_ptr<Minion> minion) {
    xw.fillRectangle(x, y, cWidth, cHeight, BLANK);
    xw.drawString(x + offset, y + offset, minion->getName());
    xw.fillRectangle(x + (cWidth * 0.8), y, cWidth * 0.2, cHeight * 0.2, COST);
    xw.drawString(x + (cWidth * 0.8) + offset, y + offset, to_string(minion->getCost()));
    xw.drawString(x + (cWidth * 0.6) + offset, y + (cHeight * 0.2) + offset, minion->getType());
    xw.fillRectangle(x, y + (cHeight * 0.8), cWidth * 0.2, cHeight * 0.2, ATK);
    xw.drawString(x + offset, y + (cHeight * 0.8) + offset, to_string(minion->getAttack()));
    xw.fillRectangle(x + (cWidth * 0.8), y + (cHeight * 0.8), cWidth * 0.2, cHeight * 0.2, DEF);
    xw.drawString(x + (cWidth * 0.8) + offset, y + (cWidth * 0.8) + offset, to_string(minion->getDefence()));
    // include activated abilities here and stuff here
}

void GraphicsDisplay::printEnchantment(int x, int y, shared_ptr<Enchantment> ench) {
    xw.fillRectangle(x, y, cWidth, cHeight, BLANK);
    xw.drawString(x + offset, y + offset, ench->getName());
    xw.fillRectangle(x + (cWidth * 0.8), y, cWidth * 0.2, cHeight * 0.2, COST);
    xw.drawString(x + (cWidth * 0.8) + offset, y + offset, to_string(ench->getCost()));
    xw.drawString(x + (cWidth * 0.6) + offset, y + (cHeight * 0.2) + offset, ench->getType());
    xw.fillRectangle(x, y + (cHeight * 0.8), cWidth * 0.2, cHeight * 0.2, ATK);
    xw.drawString(x + offset, y + (cHeight * 0.8) + offset, ench->getAtkDesc());
    xw.fillRectangle(x + (cWidth * 0.8), y + (cHeight * 0.8), cWidth * 0.2, cHeight * 0.2, DEF);
    xw.drawString(x + (cWidth * 0.8) + offset, y + (cWidth * 0.8) + offset, ench->getDefDesc());
    // include activated abilities here and stuff here
}

void GraphicsDisplay::printRitual(int x, int y, shared_ptr<Ritual> ritual) {
    xw.fillRectangle(x, y, cWidth, cHeight, BLANK);
    xw.drawString(x + offset, y + offset, ritual->getName());
    xw.fillRectangle(x + (cWidth * 0.8), y, cWidth * 0.2, cHeight * 0.2, COST);
    xw.drawString(x + (cWidth * 0.8) + offset, y + offset, to_string(ritual->getCost()));
    xw.drawString(x + (cWidth * 0.6) + offset, y + (cHeight * 0.2) + offset, ritual->getType());
    xw.fillRectangle(x + (cWidth * 0.8), y + (cHeight * 0.8), cWidth * 0.2, cHeight * 0.2, CHARGE);
    xw.drawString(x + (cWidth * 0.8) + offset, y + (cWidth * 0.8) + offset, toString(ritual->getCharge()));
    // include activated abilities here and stuff here
}

void GraphicsDisplay::printSpell(int x, int y, shared_ptr<Spell> spell) {
    xw.fillRectangle(x, y, cWidth, cHeight, BLANK);
    xw.drawString(x + offset, y + offset, spell->getName());
    xw.fillRectangle(x + (cWidth * 0.8), y, cWidth * 0.2, cHeight * 0.2, COST);
    xw.drawString(x + (cWidth * 0.8) + offset, y + offset, to_string(spell->getCost()));
    xw.drawString(x + (cWidth * 0.6) + offset, y + (cHeight * 0.2) + offset, spell->getType());
    xw.drawString(x + offset, y + (cHeight * 0.4) + offset, spell->getDesc());
}

void GraphicsDisplay::printGame(shared_ptr<Game> game) {
    xw.drawString(0, 0, "GraphicsDisplay: Printing the gameeee!");
}

void GraphicsDisplay::printHelp() {
    xw.drawString(0, cHeight * 2 + 5, 
        "Commands:\n\t"
        + "help -- Display this message,\n\t"
        + "end -- End the current player’s turn,\n\t"
        + "quit -- End the game,\n\t"
        + "attack minion other-minion -- Orders minion to attack other-minion,\n\t"
        + "attack minion -- Orders minion to attack the opponent,\n\t"
        + "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player,\n\t"
        + "use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player,\n\t"
        + "inspect minion -- View a minion’s card and all enchantments on that minion,\n\t"
        + "hand -- Describe all cards in your hand,\n\t"
        + "board -- Describe all cards on the board.");
}

void GraphicsDisplay::printDescribe(shared_ptr<Game> game, int minion) {
    auto player = game->getActivePlayer();
    auto minionCard = player->getMinions()[minion].get();

    // erase whole board
    xw.fillRectangle(0, 0, width, height);
    // needs get individual enchantment method???
    // might need get base minion method???
    printMinion(0, 0, minionCard);
    for (int i = 0; i < 100; i++) { // need individual enchantments
        
    }
    // TODO: if minion has abilities, more fields.
    // make sure to print enchantments as well
}

void GraphicsDisplay::printHand(shared_ptr<Game> game) {
    cout << "DEBUG: (GraphicsDisplay) printhand run. " << endl;
    auto player = game->getActivePlayer();
    auto hand = player->getHand();

    int y = cHeight * 5;
    for (int i = 0; i < hand->getSize(); i++) {
        int x = i * cWidth;
        // get card type, print card here
    }
}

void GraphicsDisplay::printBoard(shared_ptr<Game> game) {
    // go through everything or something idk
}