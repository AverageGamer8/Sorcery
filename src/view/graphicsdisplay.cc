#include "graphicsdisplay.h"

#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

const int ATK = Xwindow::Red;
const int DEF = Xwindow::Blue, MP = Xwindow::Blue;
const int LIFE = Xwindow::Green, COST = Xwindow::Green, CHARGE = Xwindow::Green;
const int BLANK = Xwindow::White;
const int EMPTY = Xwindow::Gray, BORDER = Xwindow::Black;
const int offset = 10, cOffset = 2 * offset;
const int lineCap = 24;
const int borderThickness = 3;

GraphicsDisplay::GraphicsDisplay(int width, int height) : xw{width, height}, width{width}, height{height}, cWidth{width / 5}, cHeight{height / 6} { xw.fillRectangle(0, 0, width, height, EMPTY); }

void GraphicsDisplay::printCard(int x, int y, shared_ptr<Card> card) {
    xw.fillRectangle(x, y, cWidth, cHeight, BLANK);
    xw.drawString(x + offset, y + offset, card->getName());
    xw.fillRectangle(x + (cWidth * 0.8), y, cWidth * 0.2, cHeight * 0.2, COST);
    xw.drawString(x + (cWidth * 0.8) + cOffset, y + cOffset, to_string(card->getCost()));
}

void GraphicsDisplay::drawDesc(int x, int y, string desc) {
    istringstream iss{desc};
    string out = "", tmp;
    int line = 0;
    for (; iss >> tmp; line++) {
        while (iss && out.length() + tmp.length() < lineCap) {
            out += tmp + " ";
            iss >> tmp;
        }
        xw.drawString(x + (offset / 2), y + (cHeight * (line * 0.1 + 0.4)) + offset, out);
        out = tmp + " ";
    }
    if (line == 1) xw.drawString(x + (offset / 2), y + (cHeight * (0.1 + 0.4)) + offset, out);
}

void GraphicsDisplay::printPlayer(int pos, shared_ptr<Player> player) {
    int left = cWidth * 2, top = pos == 0 ? 0 : cHeight * 4;
    xw.fillRectangle(left, top, cWidth, cHeight, BLANK);
    xw.drawString(left + (cWidth * 0.4), top + (pos == 0 ? cHeight * 0.4 : cHeight * 0.6), player->getName());
    xw.fillRectangle(left, top + (pos == 0 ? cHeight * 0.8 : 0), cWidth * 0.2, cHeight * 0.2, LIFE);
    xw.drawString(left + 2 * offset, top + (pos == 0 ? cHeight * 0.8 : 0) + 2 * offset, to_string(player->getLife()));
    xw.fillRectangle(left + (cWidth * 0.8), top + (pos == 0 ? cHeight * 0.8 : 0), cWidth * 0.2, cHeight * 0.2, MP);
    xw.drawString(left + (cWidth * 0.8) + 2 * offset, top + (pos == 0 ? cHeight * 0.8 : 0) + 2 * offset, to_string(player->getMagic()));
}

void GraphicsDisplay::printMinion(int x, int y, shared_ptr<Minion> minion) {
    xw.drawString(x + (cWidth * 0.6) + offset, y + (cHeight * 0.2) + offset, "Minion");
    xw.fillRectangle(x, y + (cHeight * 0.8), cWidth * 0.2, cHeight * 0.2, ATK);
    xw.drawString(x + cOffset, y + (cHeight * 0.8) + cOffset, to_string(minion->getAttack()));
    xw.fillRectangle(x + (cWidth * 0.8), y + (cHeight * 0.8), cWidth * 0.2, cHeight * 0.2, DEF);
    xw.drawString(x + (cWidth * 0.8) + cOffset, y + (cHeight * 0.8) + cOffset, to_string(minion->getDefence()));
    auto triggeredAbility = minion->getTriggeredAbility();
    auto activatedAbility = minion->getActivatedAbility();
    if (triggeredAbility)
        drawDesc(x, y, triggeredAbility->getDesc());
    else if (activatedAbility) {
        xw.fillRectangle(x, y + (cHeight * 0.4), cWidth * 0.2, cHeight * 0.2, COST);
        xw.drawString(x + cOffset, y + (cHeight * 0.4) + cOffset, to_string(minion->getActivateCost()));
        drawDesc(x + (cWidth * 0.2), y, activatedAbility->getDesc());
    }
}

void GraphicsDisplay::printEnchantment(int x, int y, shared_ptr<Enchantment> ench) {
    xw.drawString(x + (cWidth * 0.6) + offset, y + (cHeight * 0.2) + offset, "Enchantment");
    if (ench->getAtkDesc() != "") {
        xw.fillRectangle(x, y + (cHeight * 0.8), cWidth * 0.2, cHeight * 0.2, ATK);
        xw.drawString(x + offset, y + (cHeight * 0.8) + cOffset, ench->getAtkDesc());
    }
    if (ench->getDefDesc() != "") {
        xw.fillRectangle(x + (cWidth * 0.8), y + (cHeight * 0.8), cWidth * 0.2, cHeight * 0.2, DEF);
        xw.drawString(x + (cWidth * 0.8) + offset, y + (cHeight * 0.8) + cOffset, ench->getDefDesc());
    }
    drawDesc(x, y, ench->getEnchDesc());
}

void GraphicsDisplay::printRitual(int x, int y, shared_ptr<Ritual> ritual) {
    xw.drawString(x + (cWidth * 0.6) + offset, y + (cHeight * 0.2) + offset, "Ritual");
    xw.fillRectangle(x + (cWidth * 0.8), y + (cHeight * 0.8), cWidth * 0.2, cHeight * 0.2, CHARGE);
    xw.drawString(x + (cWidth * 0.8) + cOffset, y + (cHeight * 0.8) + cOffset, to_string(ritual->getCharges()));
    xw.fillRectangle(x, y + (cHeight * 0.4), cWidth * 0.2, cHeight * 0.2, COST);
    xw.drawString(x + cOffset, y + (cHeight * 0.4) + cOffset, to_string(ritual->getActivationCost()));
    drawDesc(x + (cWidth * 0.2), y, ritual->getDesc());
}

void GraphicsDisplay::printSpell(int x, int y, shared_ptr<Spell> spell) {
    xw.drawString(x + (cWidth * 0.6) + offset, y + (cHeight * 0.2) + offset, "Spell");
    xw.drawString(x + (cWidth * 0.6) + offset, y + (cHeight * 0.2) + offset, spell->getType());
    drawDesc(x, y, spell->getDesc());
}

void GraphicsDisplay::printSorcery() {
    int x = cWidth * 2, y = cHeight * 2;
    xw.fillRectangle(x, y, cWidth, cHeight, BLANK);
    xw.drawString(x + 6 * offset, y + 6 * offset, "SORCERY");
}

void GraphicsDisplay::printHelp() {
    xw.fillRectangle(0, cHeight * 2, cWidth * 2, cHeight, BLANK);
    const string temp = "";
    xw.drawString(0, cHeight * 2 + (1 * offset), "Commands:");
    xw.drawString(0, cHeight * 2 + (2 * offset), "help -- Display this message,");
    xw.drawString(0, cHeight * 2 + (3 * offset), "end -- End the current player's turn,");
    xw.drawString(0, cHeight * 2 + (4 * offset), "quit -- End the game,");
    xw.drawString(0, cHeight * 2 + (5 * offset), "attack minion other-minion -- Orders minion to attack");
    xw.drawString(0, cHeight * 2 + (6 * offset), "                              other-minion,");
    xw.drawString(0, cHeight * 2 + (7 * offset), "attack minion -- Orders minion to attack the opponent,");
    xw.fillRectangle(cWidth * 3, cHeight * 2, cWidth * 2, cHeight, BLANK);
    xw.drawString(cWidth * 3, cHeight * 2 + (1 * offset), "play card [target-player target-card] -- Play card, optionally ");
    xw.drawString(cWidth * 3, cHeight * 2 + (2 * offset), "          targeting target-card owned by target-player,");
    xw.drawString(cWidth * 3, cHeight * 2 + (3 * offset), "use minion [target-player target-card] -- Use minion's special");
    xw.drawString(cWidth * 3, cHeight * 2 + (4 * offset), "ability, optionally targeting target-card owned by target-player,");
    xw.drawString(cWidth * 3, cHeight * 2 + (5 * offset), "inspect minion -- View a minion's card and all enchantments");
    xw.drawString(cWidth * 3, cHeight * 2 + (6 * offset), "                  on that minion,");
    xw.drawString(cWidth * 3, cHeight * 2 + (7 * offset), "hand -- Describe all cards in your hand,");
    xw.drawString(cWidth * 3, cHeight * 2 + (8 * offset), "board -- Describe all cards on the board.");
}

void GraphicsDisplay::printDescribe(Game* game, int minion) {
    auto player = game->getActivePlayer();
    auto target = player->getMinions()[minion];

    xw.fillRectangle(0, 0, width, height, EMPTY);
    printCard(0, 0, static_pointer_cast<Card>(target));
    printMinion(0, 0, target);
    vector<shared_ptr<Enchantment>> enchs;
    while (target->getType() == "Enchantment") {
        auto ench = static_pointer_cast<Enchantment>(target);
        enchs.emplace_back(ench);
        target = ench->getMinion();
    }
    reverse(enchs.begin(), enchs.end());
    for (size_t pos = 0; pos < enchs.size(); pos++) {
        int x = (pos % 5) * cWidth, y = ((pos / 5) + 1) * cHeight;
        auto ench = enchs[pos];
        xw.fillRectangle(x, y, cWidth, cHeight, BLANK);
        xw.drawString(x + offset, y + offset, ench->getEnchName());
        xw.fillRectangle(x + (cWidth * 0.8), y, cWidth * 0.2, cHeight * 0.2, COST);
        xw.drawString(x + (cWidth * 0.8) + cOffset, y + cOffset, to_string(ench->getEnchCost()));
        xw.drawString(x + (cWidth * 0.6) + offset, y + (cHeight * 0.2) + offset, ench->getType());
        printEnchantment(x, y, ench);
    }
}

void GraphicsDisplay::printHand(Game* game) {
    auto player = game->getActivePlayer();
    auto hand = player->getHand();
    int y = cHeight * 5;
    xw.fillRectangle(0, y, width, cHeight, BLANK);
    for (int i = 0; i < hand->getSize(); i++) {
        int x = i * cWidth;
        auto card = hand->getCardAtIndex(i);
        printCard(x, y, card);
        if (card->getType() == "Minion")
            printMinion(x, y, static_pointer_cast<Minion>(card));
        else if (card->getType() == "Enchantment")
            printEnchantment(x, y, static_pointer_cast<Enchantment>(card));
        else if (card->getType() == "Ritual")
            printRitual(x, y, static_pointer_cast<Ritual>(card));
        else if (card->getType() == "Spell")
            printSpell(x, y, static_pointer_cast<Spell>(card));
    }
    xw.fillRectangle(0, cHeight * 5 - borderThickness, width, borderThickness, BORDER);
}

void GraphicsDisplay::printBoard(Game* game) {
    xw.fillRectangle(0, 0, width, height, EMPTY);
    // print player 0
    auto player = game->getPlayer(0);
    printPlayer(0, player);
    auto ritual = player->getBoard()->getRitual();
    if (ritual) {
        printCard(0, 0, static_pointer_cast<Card>(ritual));
        printRitual(0, 0, ritual);
    } else {
        xw.fillRectangle(0, 0, cWidth, cHeight, Xwindow::Blue);
        xw.drawString(2 * cOffset, 2 * cOffset, "Ritual: Empty");
    }
    if (!player->getGraveyard()->isEmpty()) {
        auto graveTop = player->getGraveyard()->getTopMinion();
        printCard(cWidth * 4, 0, static_pointer_cast<Card>(graveTop));
        printMinion(cWidth * 4, 0, graveTop);
    } else {
        xw.fillRectangle(cWidth * 4, 0, cWidth, cHeight, Xwindow::Green);
        xw.drawString(cWidth * 4 + 2 * cOffset, 2 * cOffset, "Graveyard: Empty");
    }
    auto minions = player->getBoard()->getMinions();
    for (int i = 0; i < 5; i++) xw.fillRectangle(cWidth * i, cHeight, cWidth, cHeight, BLANK);
    for (size_t i = 0; i < minions.size(); i++) {
        printCard(cWidth * i, cHeight, static_pointer_cast<Card>(minions[i]));
        printMinion(cWidth * i, cHeight, minions[i]);
    }
    // print player 1
    player = game->getPlayer(1);
    printPlayer(1, player);
    ritual = player->getBoard()->getRitual();
    if (ritual) {
        printCard(0, cHeight * 4, static_pointer_cast<Card>(ritual));
        printRitual(0, cHeight * 4, ritual);
    } else {
        xw.fillRectangle(0, cHeight * 4, cWidth, cHeight, Xwindow::Blue);
        xw.drawString(2 * cOffset, cHeight * 4 + 2 * cOffset, "Ritual: Empty");
    }
    if (!player->getGraveyard()->isEmpty()) {
        auto graveTop = player->getGraveyard()->getTopMinion();
        printCard(cWidth * 4, cHeight * 4, static_pointer_cast<Card>(graveTop));
        printMinion(cWidth * 4, cHeight * 4, graveTop);
    } else {
        xw.fillRectangle(cWidth * 4, cHeight * 4, cWidth, cHeight, Xwindow::Green);
        xw.drawString(cWidth * 4 + 2 * cOffset, cHeight * 4 + 2 * cOffset, "Graveyard: Empty");
    }
    minions = player->getBoard()->getMinions();
    for (int i = 0; i < 5; i++) xw.fillRectangle(cWidth * i, cHeight * 3, cWidth, cHeight, BLANK);
    for (size_t i = 0; i < minions.size(); i++) {
        printCard(cWidth * i, cHeight * 3, static_pointer_cast<Card>(minions[i]));
        printMinion(cWidth * i, cHeight * 3, minions[i]);
    }
    printSorcery();
    printHelp();
    printHand(game);
}
