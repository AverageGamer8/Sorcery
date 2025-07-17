#include "textdisplay.h"

TextDisplay::TextDisplay(std::ostream &out) : out{out} {}

void TextDisplay::printGame(std::shared_ptr<Game> game) {
    out << "TextDisplay: Printing the gameeee!" << std::endl;
}

void TextDisplay::printHelp() {
    out << "Commands:\n"
    << "help -- Display this message,\n"
    << "end -- End the current player’s turn,\n"
    << "quit -- End the game,\n"
    << "attack minion other-minion -- Orders minion to attack other-minion,\n"
    << "attack minion -- Orders minion to attack the opponent,\n"
    << "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player,\n"
    << "use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player,\n"
    << "inspect minion -- View a minion’s card and all enchantments on that minion,\n"
    << "hand -- Describe all cards in your hand,\n"
    << "board -- Describe all cards on the board."
    << std::endl;
}