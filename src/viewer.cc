#include "viewer.h"

Viewer::Viewer(std::vector<std::shared_ptr<Display>> displays, std::shared_ptr<Game> game) 
    : displays{displays}, game{game} {}

void Viewer::display(Command command) {
    for (auto &d : displays) { // do the command for all active displays
        switch (command) {
            case PRINT:
                d->printGame(game);
                break;
            case HELP:
                d->printHelp();
                break;
        }
    }
}