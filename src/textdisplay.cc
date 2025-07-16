#include "textdisplay.h"

TextDisplay::TextDisplay(std::ostream &out) : out{out} {}

void TextDisplay::printGame(std::shared_ptr<Game> game) {
    out << "TextDisplay: Printing the gameeee!" << std::endl;
}

void TextDisplay::printHelp() {
    out << "======= Commands: ======== \n - awhriuweifhwefoij" << std::endl;
}