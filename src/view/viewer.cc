#include "viewer.h"

Viewer::Viewer(std::vector<std::shared_ptr<Display>> displays, std::shared_ptr<Game> game)
    : displays{displays}, game{game} {}

// TODO: possible find a better way to do switching with multiple. 
// Maybe just have 1 func with context struct.
void Viewer::display(Command command) {
    for (auto &d : displays) {  // do the command for all active displays
        switch (command) {
            case PRINT:
                d->printGame(game);
                break;
            case HELP:
                d->printHelp();
                break;
            case HAND:
                d->printHand(game);
                break;
            case BOARD:
                d->printBoard(game);
                break
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