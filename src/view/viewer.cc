#include "viewer.h"

Viewer::Viewer(std::vector<std::shared_ptr<sorcDisplay>> displays, Game *game)
    : displays{displays}, game{game} {}

void Viewer::display(Command command) {
    for (auto &d : displays) {  // do the command for all active displays
        switch (command) {
            case HELP:
                d->printHelp();
                break;
            case HAND:
                d->printHand(game);
                break;
            case BOARD:
                d->printBoard(game);
                break;
        }
    }
}
void Viewer::display(Command command, int minion) {
    for (auto &d : displays) {  // do the command for all active displays
        switch (command) {
            case DESCRIBE:
                d->printDescribe(game, minion);
                break;
        }
    }
}
