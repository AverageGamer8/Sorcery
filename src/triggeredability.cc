#include "triggeredability.h"

#include <iostream>  // TODO: remove debugs
#include <memory>

#include "./gameModel/game.h"

using namespace std;

void TriggeredAbility::notify() {
    if (shouldTrigger()) {
        activate();
    }
}

OnStartGainMagic::OnStartGainMagic(shared_ptr<Game> game, int player) : TriggeredAbility{game, player} {}
void OnStartGainMagic::activate() {  // gains 1 magic at start of turn.
    auto p = game->getPlayer(player);
    cout << "DEBUG: TriggeredAbility) OnStartGainMagic: activated " << endl;

    auto ritual = p->getBoard()->getRitual();
    if (ritual && ritual->getCharges() <= 0) {
        cout << "DEBUG: (TriggeredAbility) No more charges. Removed ritual" << endl;
        p->getBoard()->removeRitual();
        return;
    }
    p->setMagic(p->getMagic() + 1);
    ritual->setCharges(ritual->getCharges() - 1);
}
bool OnStartGainMagic::shouldTrigger() const {
    return game->getActiveIndex() == player;
}

OnEnterBuff::OnEnterBuff(shared_ptr<Game> game, int player) : TriggeredAbility{game, player} {}
void OnEnterBuff::activate() {
    auto p = game->getPlayer(player);
    cout << "DEBUG: (TriggeredAbility) OnEnterBuff: activated " << endl;

    auto ritual = p->getBoard()->getRitual();
    if (ritual && ritual->getCharges() <= 0) {
        cout << "DEBUG: (TriggeredAbility) No more charges. Removed ritual" << endl;
        p->getBoard()->removeRitual();
        return;
    }
    // TODO: buff new minion
    ritual->setCharges(ritual->getCharges() - 1);
}
bool OnEnterBuff::shouldTrigger() const {
    return true;
}

OnEnterDestroy::OnEnterDestroy(shared_ptr<Game> game, int player) : TriggeredAbility{game, player} {}
void OnEnterDestroy::activate() {
    auto p = game->getPlayer(player);
    cout << "DEBUG: (TriggeredAbility) OnEnterDestroy: activated " << endl;

    auto ritual = p->getBoard()->getRitual();
    if (ritual && ritual->getCharges() <= 0) {
        cout << "DEBUG: (TriggeredAbility) No more charges. Removed ritual" << endl;
        p->getBoard()->removeRitual();
        return;
    }
    // TODO: destroy added minion.
    ritual->setCharges(ritual->getCharges() - 1);
}
bool OnEnterDestroy::shouldTrigger() const {
    return true;
}
