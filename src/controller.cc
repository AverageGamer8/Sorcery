#include "controller.h"

Controller::Controller(std::shared_ptr<Game> game,
                       std::shared_ptr<Viewer> viewer)
    : game{game}, viewer{viewer} {}

// TODO: once cards work, uncomment.

// void Controller::drawCard() {
//     auto player = game.get()->getActivePlayer();
//     player->drawCard();
// }

// void Controller::end() {
//     game->endTurn();
//     game->startTurn();
// }

// -------------- Display Controls -------------

// Calls virtual function on all displays

void Controller::help() {
    viewer->display(Viewer::HELP);
}