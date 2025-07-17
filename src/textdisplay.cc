#include "textdisplay.h"

TextDisplay::TextDisplay(std::ostream &out) : out{out} {}

void TextDisplay::printGame(std::shared_ptr<Game> game) {
    out << "TextDisplay: Printing the gameeee!" << std::endl;
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
        << std::endl;
}