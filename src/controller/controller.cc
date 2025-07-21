#include "controller.h"
#include <iostream> // TODO remove debug

Controller::Controller(std::shared_ptr<Game> game,
                       std::shared_ptr<Viewer> viewer)
    : game{game}, viewer{viewer} {}

// ======================= Player/Game Controls ===================

void Controller::end() {
    game->endTurn();
    game->startTurn();
}
void Controller::draw() {
    auto player = game.get()->getActivePlayer();
    player->drawCard();
}

void Controller::discard(int card) {
    auto player = game.get()->getActivePlayer();
    player->discardCard(card);
}

void Controller::attack(int attackingMinion) {
    auto player = game.get()->getActivePlayer();
    player->minionAttack(attackingMinion);  // attack player.
}

void Controller::attack(int attackingMinion, int receivingMinion) {
    auto player = game.get()->getActivePlayer();
    auto player2 = game.get()->getInactivePlayer();
    
    player->minionAttack(attackingMinion, receivingMinion);
}

void Controller::play(int card) {
    game->playCard(card);
}

void Controller::play(int card, int onPlayer, int minion) {
    auto player = game.get()->getActivePlayer();
    player->playCard(card, onPlayer, minion);
}

void Controller::use(int minion) {
    auto player = game.get()->getActivePlayer();
    player->activateCard(minion);
}

void Controller::use(int activeMinion, int onPlayer, int receivingMinion) {
    auto player = game.get()->getActivePlayer();
    player->activateCard(activeMinion, onPlayer, receivingMinion);
}

// ======================= Display Controls ====================

// Calls virtual function on all displays

void Controller::help() {
    viewer->display(Viewer::HELP);
}

void Controller::describe(int minion) {  // TODO!! figure out how to pass minion?
    viewer->display(Viewer::DESCRIBE, minion);
    // my current solution: use overloaded display().
}

void Controller::hand() {
    viewer->display(Viewer::HAND);
}

void Controller::board() {
    viewer->display(Viewer::BOARD);
}