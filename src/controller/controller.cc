#include "controller.h"
#include "../argexception.h"

#include <iostream>  // TODO remove debug

Controller::Controller(Game* game,
                       std::shared_ptr<Viewer> viewer)
    : game{game}, viewer{viewer} {}

// ======================= Player/Game Controls ===================

void Controller::end() {
    game->endTurn();
    game->startTurn();
}
void Controller::draw() {
    auto player = game->getActivePlayer();
    player->drawCard();
}

bool Controller::discard(int card) {
    auto player = game->getActivePlayer();
    if (card < 0 || card >= player->getHand()->getSize()) return false;
    player->discardCard(card);
    return true;
}

bool Controller::attack(int attackingMinion) {
    auto player = game->getActivePlayer();
    if (attackingMinion < 0 || attackingMinion >= player->getMinions().size()) {
        return false;
    }
    try {
        player->minionAttack(attackingMinion);  // attack player.
    }
    catch (ArgException& e) {
        cerr << e.what();
        return false;
    }
    return true;
}

bool Controller::attack(int attackingMinion, int receivingMinion) {
    auto player1 = game->getActivePlayer();
    auto player2 = game->getInactivePlayer();
    if (attackingMinion < 0 || attackingMinion >= player1->getMinions().size() 
        || receivingMinion < 0 || receivingMinion >= player2->getMinions().size()) {
        return false;
    }
    try {
        player1->minionAttack(attackingMinion, receivingMinion);
    }
    catch (ArgException& e) {
        cerr << e.what();
        return false;
    }
    return true;
}

bool Controller::play(int card, bool testingEnabled) {
    if (card < 0 || card >= game->getActivePlayer()->getHand()->getSize()) return false;
    if (!game->playCard(card, testingEnabled)) return false;  // Minion enters.
    return true;
}

bool Controller::play(int card, int onPlayer, int minion, bool testingEnabled) {
    auto player = game->getActivePlayer();
    auto receivingPlayer = game->getPlayer(onPlayer);
    if (card < 0 || card >= player->getHand()->getSize() 
        || onPlayer < 0 || onPlayer >= 2
        || (minion != -1 && (minion < 0 || minion >= receivingPlayer->getMinions().size()))) {
        return false;
    }
    if (minion == -1) { // ritual
        try {
            player->playCard(card, onPlayer, testingEnabled);
        }
        catch (ArgException& e) {
            cerr << e.what() << endl;
            return false;
        }
        return true;
    }
    try {
        player->playCard(card, onPlayer, minion, testingEnabled);
    }
    catch (ArgException& e) {
        cerr << e.what() << endl;
        return false;
    }
    return true;
}

bool Controller::use(int minion, bool testingEnabled) {
    auto player = game->getActivePlayer();
    if (minion < 0 || minion >= player->getMinions().size()) return false;
    try {
        player->activateCard(minion, testingEnabled);
    }
    catch (ArgException& e) {
        cerr << e.what() << endl;
        return false;
    }
    return true;
}

bool Controller::use(int activeMinion, int onPlayer, int receivingMinion, bool testingEnabled) {
    auto player = game->getActivePlayer();
    auto receivingPlayer = game->getPlayer(onPlayer);
    if (activeMinion < 0 || activeMinion >= player->getMinions().size()
        || onPlayer < 0 || onPlayer >= 2
        || receivingMinion < 0 || receivingMinion >= receivingPlayer->getMinions().size()) {
            return false;
        }
    try {
        player->activateCard(activeMinion, onPlayer, receivingMinion, testingEnabled);
    }
    catch (ArgException& e) {
        cerr << e.what() << endl;
        return false;
    }
    return true;
}

// ======================= Display Controls ====================

// Calls virtual function on all displays

void Controller::help() {
    viewer->display(Viewer::HELP);
}

bool Controller::describe(int minion) {  // TODO!! figure out how to pass minion?
    if (minion < 0 || minion >= game->getActivePlayer()->getMinions().size()) throw ArgException("Invalid minion index provided.");
    viewer->display(Viewer::DESCRIBE, minion);
    return true;
    // my current solution: use overloaded display().
}

void Controller::hand() {
    viewer->display(Viewer::HAND);
}

void Controller::board() {
    viewer->display(Viewer::BOARD);
}