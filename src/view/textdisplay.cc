#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay(ostream &out) : out{out} {}

void TextDisplay::printCardTemplate(const card_template_t& cardInfo) {
    for (const auto& line : cardInfo) {
        out << line << endl;
    }
}

void TextDisplay::printGame(shared_ptr<Game> game) {
    out << "TextDisplay: Printing the gameeee!" << endl;
}

void TextDisplay::printHelp() {
    out << "Commands:\n\t"
        << "help -- Display this message,\n\t"
        << "end -- End the current player’s turn,\n\t"
        << "quit -- End the game,\n\t"
        << "attack minion other-minion -- Orders minion to attack other-minion,\n\t"
        << "attack minion -- Orders minion to attack the opponent,\n\t"
        << "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player,\n\t"
        << "use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player,\n\t"
        << "inspect minion -- View a minion’s card and all enchantments on that minion,\n\t"
        << "hand -- Describe all cards in your hand,\n\t"
        << "board -- Describe all cards on the board."
        << endl;
}
void printDescribe(shared_ptr<Game> game, int minion) {
    auto player = game->getActivePlayer();
    auto minionCard = player->getMinions()[minion];

    card_template_t cardInfo;
    // TODO: if minion has abilities, more fields.

    cardInfo = display_minion_no_ability(
        minionCard->getName(),
        minionCard->getCost(),
        minionCard->getAttack(),
        minionCard->getDefense()
    );
    printCardTemplate(cardInfo);
}


void printHand(shared_ptr<Game> game) {
    auto player = game->getActivePlayer();
    auto hand = player->getHand();
    
}

void printBoard(shared_ptr<Game> game) {

}