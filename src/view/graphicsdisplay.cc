#include "graphicsdisplay.h"
#include <sstream>

using namespace std;

const int ATK = Xwindow::Red;
const int DEF = Xwindow::Blue, MP = Xwindow::Blue;
const int LIFE = Xwindow::Green, COST = Xwindow::Green, CHARGE = Xwindow::Green;
const int BLANK = Xwindow::White;
const int EMPTY = Xwindow::Black;
const int offset = 10, cOffset = 2 * offset;
const int lineCap = 22;

GraphicsDisplay::GraphicsDisplay(int width, int height) : 
    xw{width, height}, width{width}, height{height}, cWidth{width / 5}, cHeight{height / 6} { xw.fillRectangle(0, 0, width, height); }

void GraphicsDisplay::printCard(int x, int y, shared_ptr<Card> card) {
    xw.fillRectangle(x, y, cWidth, cHeight, BLANK);
    xw.drawString(x + offset, y + offset, card->getName());
    xw.fillRectangle(x + (cWidth * 0.8), y, cWidth * 0.2, cHeight * 0.2, COST);
    xw.drawString(x + (cWidth * 0.8) + cOffset, y + cOffset, to_string(card->getCost()));
    xw.drawString(x + (cWidth * 0.6) + offset, y + (cHeight * 0.2) + offset, card->getType());
}

void GraphicsDisplay::drawDesc(int x, int y, string desc) {
    istringstream iss{desc}; string out = "";
    for (int line = 0; iss >> out; line++) {
        string tmp = "";
        while (out.length() < lineCap && iss >> tmp) out += " " + tmp;
        xw.drawString(x + offset, y + (cHeight * (line * 0.1 + 0.4)) + offset, out);
        out = "";
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
    xw.fillRectangle(x, y + (cHeight * 0.8), cWidth * 0.2, cHeight * 0.2, ATK);
    xw.drawString(x + cOffset, y + (cHeight * 0.8) + cOffset, to_string(minion->getAttack()));
    xw.fillRectangle(x + (cWidth * 0.8), y + (cHeight * 0.8), cWidth * 0.2, cHeight * 0.2, DEF);
    xw.drawString(x + (cWidth * 0.8) + cOffset, y + (cHeight * 0.8) + cOffset, to_string(minion->getDefence()));
    // include activated abilities here and stuff here
}

void GraphicsDisplay::printEnchantment(int x, int y, shared_ptr<Enchantment> ench) {
    if (ench->getAtkDesc() != "") {
        xw.fillRectangle(x, y + (cHeight * 0.8), cWidth * 0.2, cHeight * 0.2, ATK);
        xw.drawString(x + cOffset, y + (cHeight * 0.8) + cOffset, ench->getAtkDesc());
    }
    if (ench->getDefDesc() != "") {
        xw.fillRectangle(x + (cWidth * 0.8), y + (cHeight * 0.8), cWidth * 0.2, cHeight * 0.2, DEF);
        xw.drawString(x + (cWidth * 0.8) + cOffset, y + (cHeight * 0.8) + cOffset, ench->getDefDesc());
    }
    drawDesc(x, y, ench->getEnchDesc());
}

void GraphicsDisplay::printRitual(int x, int y, shared_ptr<Ritual> ritual) {
    xw.fillRectangle(x + (cWidth * 0.8), y + (cHeight * 0.8), cWidth * 0.2, cHeight * 0.2, CHARGE);
    xw.drawString(x + (cWidth * 0.8) + cOffset, y + (cHeight * 0.8) + cOffset, to_string(ritual->getCharges()));
    xw.fillRectangle(x, y + (cHeight * 0.4), cWidth * 0.2, cHeight * 0.2, COST);
    xw.drawString(x + cOffset, y + (cHeight * 0.4) + cOffset, to_string(ritual->getActivationCost()));
    drawDesc(x + (cWidth * 0.2), y, ritual->getDesc());
}

void GraphicsDisplay::printSpell(int x, int y, shared_ptr<Spell> spell) {
    xw.drawString(x + (cWidth * 0.6) + offset, y + (cHeight * 0.2) + offset, spell->getType());
    drawDesc(x, y, spell->getDesc());
}

void GraphicsDisplay::printSorcery() {
    int x = cWidth * 2, y = cHeight * 2;
    xw.fillRectangle(x, y, cWidth, cHeight, BLANK);
    xw.drawString(x + 3 * offset, y + 3 * offset, "SORCERY");
}

void GraphicsDisplay::printHelp() {
    xw.fillRectangle(0, cHeight * 2, cWidth * 2, cHeight, BLANK);
    const string temp = "";
    xw.drawString(0, cHeight * 2 + offset, 
        temp + "Commands:\n\t"
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

void GraphicsDisplay::printDescribe(Game* game, int minion) {
    auto player = game->getActivePlayer();
    auto target = player->getMinions()[minion];

    xw.fillRectangle(0, 0, width, height);
    printCard(0, 0, static_pointer_cast<Card>(target));
    printMinion(0, 0, target);
    int pos = 0;
    while (target->getType() == "Enchantment") {
        int x = (pos % 5) * cWidth, y = ((pos / 5) + 1) * cHeight;
        auto ench = static_pointer_cast<Enchantment>(target);
        xw.fillRectangle(x, y, cWidth, cHeight, BLANK);
        xw.drawString(x + offset, y + offset, ench->getEnchName());
        xw.fillRectangle(x + (cWidth * 0.8), y, cWidth * 0.2, cHeight * 0.2, COST);
        xw.drawString(x + (cWidth * 0.8) + cOffset, y + cOffset, to_string(ench->getEnchCost()));
        xw.drawString(x + (cWidth * 0.6) + offset, y + (cHeight * 0.2) + offset, ench->getType());
        printEnchantment(x, y, ench);
        target = ench->getMinion();
    }
}

void GraphicsDisplay::printHand(Game* game) {
    cout << "DEBUG: (GraphicsDisplay) printhand run. " << endl;
    auto player = game->getActivePlayer();
    auto hand = player->getHand();

    int y = cHeight * 5;
    for (int i = 0; i < hand->getSize(); i++) {
        int x = i * cWidth;
        auto card = hand->getCardAtIndex(i);
        printCard(x, y, card);
        printCard(x, y, card);
        if (card->getType() == "Minion") printMinion(x, y, static_pointer_cast<Minion>(card));
        else if (card->getType() == "Enchantment") printEnchantment(x, y, static_pointer_cast<Enchantment>(card));
        else if (card->getType() == "Ritual") printRitual(x, y, static_pointer_cast<Ritual>(card));
        else if (card->getType() == "Spell") printSpell(x, y, static_pointer_cast<Spell>(card));
    }
}

void GraphicsDisplay::printBoard(Game* game) {
    // go through everything or something idk


    printSorcery();
    printHand(game);
}