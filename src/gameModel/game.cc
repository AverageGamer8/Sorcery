#include "game.h"

#include "../narrator.h"
#include "../argexception.h"

using namespace std;

Game::Game(vector<shared_ptr<Player>> players)
    : players{players} { }

void Game::startTurn() {
    Narrator::printLine();
    Narrator::announce("Player " + to_string(getActiveIndex() + 1) + ": '" + getActivePlayer()->getName() + "' starts their turn...");
    auto player = getActivePlayer();

    player->setMagic(player->getMagic() + 1);
    Narrator::announce("Magic restored and minions refreshed!");

    auto hand = player->getHand();
    auto board = player->getBoard();
    for (auto card : hand->getCards()) {
        if (card->getType() == "Minion") {
            auto minion = static_pointer_cast<Minion>(card);
            minion->restoreAction();
        }
    }
    for (auto minion : board->getMinions()) {
        minion->restoreAction();
    }

    player->drawCard();
    Narrator::announce("A new card is drawn from the deck.");
    notifyTrigger(Trigger::TriggerType::TurnStart);
}

void Game::endTurn() {
    Narrator::announce("Player " + to_string(getActiveIndex() + 1) + ": '" + getActivePlayer()->getName() + "' ends their turn.");
    notifyTrigger(Trigger::TriggerType::TurnEnd);
    activePlayer = (activePlayer == 0) ? 1 : 0;  // swap turn
}

void Game::handleMinionDeath(int player, int minion) {
    auto p = getPlayer(player);
    p->getGraveyard()->addMinion(p->getBoard()->removeMinion(minion));
}

void Game::battleMinion(shared_ptr<Minion> attackingMinion, int receivingMinion) {
    auto attacker = getActivePlayer();
    auto opp = getInactivePlayer();
    auto oppMinion = opp->getBoard()->getMinion(receivingMinion);
    Narrator::announce(attackingMinion->getName() + " (ATK:" + to_string(attackingMinion->getAttack()) +
                       ", DEF:" + to_string(attackingMinion->getDefence()) + ") battles " +
                       oppMinion->getName() + " (ATK:" + to_string(oppMinion->getAttack()) +
                       ", DEF:" + to_string(oppMinion->getDefence()) + ")!");

    if (oppMinion->takeDamage(attackingMinion->getAttack())) {
        Narrator::announce(oppMinion->getName() + " has fallen while defending!");
        handleMinionDeath(getInactiveIndex(), receivingMinion);
    }
    if (attackingMinion->takeDamage(oppMinion->getAttack())) {
        Narrator::announce(attackingMinion->getName() + " has been defeated while attacking!");
        int attackerIndex;
        try {
             attackerIndex = attacker->getBoard()->getMinionIndex(attackingMinion);
        }
        catch (ArgException& e) {
            cerr << e.what() << endl;
            return;
        }
        handleMinionDeath(getActiveIndex(), attackerIndex);
    }
}

bool Game::playCard(int card, bool testingEnabled) {  // Wrapper to notify MinionEnter observers
    auto player = getActivePlayer();
    auto cardPtr = player->getHand()->getCardAtIndex(card);
    try {
        player->playCard(card, testingEnabled);
    }
    catch (ArgException& e) {
        cerr << e.what() << endl;
        return false;
    }
    if (cardPtr->getType() == "Minion") {
        notifyTrigger(Trigger::TriggerType::MinionEnter);
    }
    return true;
}

void Game::setActivePlayer(int player) { activePlayer = player; }
void Game::setWinner(int winner) { winningPlayer = winner; }
int Game::getWinner() const { return winningPlayer; }

shared_ptr<Player> Game::getPlayer(int index) { return players[index]; }
shared_ptr<Player> Game::getActivePlayer() { return getPlayer(activePlayer); }
shared_ptr<Player> Game::getInactivePlayer() { return getPlayer(getInactiveIndex()); }

int Game::getInactiveIndex() {
    return (activePlayer + 1) % 2;
}

int Game::getActiveIndex() {
    return activePlayer;
}

void Game::notifyTrigger(Trigger::TriggerType type) {
    auto activePlayer = getActivePlayer();
    auto inactivePlayer = getInactivePlayer();

    for (auto& minion : activePlayer->getBoard()->getMinions()) {
        if (minion->getTriggeredAbility() && minion->getTriggeredAbility()->getTriggerType() == type) {
            minion->getTriggeredAbility()->notify();
        }
    }
    if (activePlayer->hasRitual() && activePlayer->getBoard()->getRitual()->getTriggeredAbility()->getTriggerType() == type) {
        activePlayer->getBoard()->getRitual()->getTriggeredAbility()->notify();
    }

    for (auto& minion : inactivePlayer->getBoard()->getMinions()) {
        if (minion->getTriggeredAbility() && minion->getTriggeredAbility()->getTriggerType() == type) {
            minion->getTriggeredAbility()->notify();
        }
    }
    if (inactivePlayer->hasRitual() && inactivePlayer->getBoard()->getRitual()->getTriggeredAbility()->getTriggerType() == type) {
        inactivePlayer->getBoard()->getRitual()->getTriggeredAbility()->notify();
    }
}
