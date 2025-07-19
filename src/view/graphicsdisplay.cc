#include "graphicsdisplay.h"

#include "../cards/spell.h"  // TODO: investigate dependecny this shouldnt be needed
using namespace std;

// red: attack
// blue: defence, magic
// green: player life, ritual charges
const ATK = Xwindow::Red;
const DEF = Xwindow::Blue, MP = Xwindow::Blue;
const LIFE = Xwindow::Green;
const BLANK = Xwindow::White;
const EMPTY = Xwindow::Black;

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

void GraphicsDisplay::printPlayer(int pos, std::string name, int life, int magic) {
    int left = cWidth * 2, top = pos == 0 ? 0 : cHeight * 4;
    xw.fillRectangle(left, top, cWidth, cHeight, BLANK);
    xw.drawString(left + (cWidth * 0.4), top + (pos == 0 ? cHeight * 0.2 : cHeight * 0.6), name);
    xw.fillRectangle(left, top + (pos == 0 ? cHeight * 0.8 : 0), cWidth * 0.2, cHeight * 0.2, LIFE);
    xw.drawString(left + 10, top + (pos == 0 ? cHeight * 0.8 : 0) + 10, life + "");
    xw.fillRectangle(left + (cWidth * 0.8), top + (pos == 0 ? cHeight * 0.8 : 0), cWidth * 0.2, cHeight * 0.2, MP);
    xw.drawString(left + (cWidth * 0.8) + 10, top + (pos == 0 ? cHeight * 0.8 : 0) + 10, magic + "");
}

void GraphicsDisplay::printGame(shared_ptr<Game> game) {
    xw.drawString(0, 0, "GraphicsDisplay: Printing the gameeee!");
}

void GraphicsDisplay::printHelp() {
    xw.drawString(width / 2, height / 2, 
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

    card_template_t cardInfo;
    // TODO: if minion has abilities, more fields.

    cardInfo = display_minion_no_ability(
        minionCard->getName(),
        minionCard->getCost(),
        minionCard->getAttack(),
        minionCard->getDefence());
    printCardTemplate(cardInfo);
}

void GraphicsDisplay::printHand(shared_ptr<Game> game) {
    cout << "DEBUG: (GraphicsDisplay) printhand run. " << endl;
    auto player = game->getActivePlayer();
    auto hand = player->getHand();

    vector<card_template_t> cardTemplates;
    for (int i = 0; i < hand->getSize(); ++i) {
        auto card = hand->getCardAtIndex(i);
        card_template_t cardInfo;

        if (card->getType() == "Minion") {
            auto minion = static_cast<Minion*>(card.get());
            cardInfo = display_minion_no_ability(  // TODO other abilities.
                minion->getName(),
                minion->getCost(),
                minion->getAttack(),
                minion->getDefence());
        } else if (card->getType() == "Spell") {
            auto spell = static_cast<Spell*>(card.get());
            cardInfo = display_spell(
                spell->getName(),
                spell->getCost(),
                spell->getDesc());
        } else {                                   // TODO: Other cards
            cardInfo = display_minion_no_ability(  // This is a filler.
                "Empty.",
                -99,
                -99,
                -99);
        }
        cardTemplates.emplace_back(cardInfo);
        // printCardTemplate(cardInfo);
    }
    if (!cardTemplates.empty()) {  // Print them horizontally
        int height = cardTemplates[0].size();
        for (int line = 0; line < height; ++line) {
            for (int card = 0; card < cardTemplates.size(); ++card) {
                out << cardTemplates[card][line];
            }
            if (line < height - 1) {
                out << endl;
            }
        }
    }
    out << endl;
}

void GraphicsDisplay::printBoard(shared_ptr<Game> game) {
}