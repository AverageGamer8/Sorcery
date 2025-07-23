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

OnStartGainMagic::OnStartGainMagic(Game* game, int player) : TriggeredAbility{game, player} {}
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

OnEnterBuff::OnEnterBuff(Game* game, int player) : TriggeredAbility{game, player} {}
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
    auto& minions = p->getBoard()->getMinions();
    if (!minions.empty()) {
        auto minion = minions.back();
        minion->setDefence(minion->getDefence() + 1);
        minion->setAttack(minion->getAttack() + 1);
        cout << "DEBUG: (TriggeredAbility) OnEnterBuff: Buffed newly entered minion +1/+1" << endl;
        ritual->setCharges(ritual->getCharges() - 1);
    }
}
bool OnEnterBuff::shouldTrigger() const {
    return true;
}

OnEnterDestroy::OnEnterDestroy(Game* game, int player) : TriggeredAbility{game, player} {}
void OnEnterDestroy::activate() {
    auto p = game->getPlayer(player);
    cout << "DEBUG: (TriggeredAbility) OnEnterDestroy: activated " << endl;

    auto ritual = p->getBoard()->getRitual();
    if (ritual && ritual->getCharges() <= 0) {
        cout << "DEBUG: (TriggeredAbility) No more charges. Removed ritual" << endl;
        p->getBoard()->removeRitual();
        return;
    }
    if (!ritual) return;
    // TODO: destroy added minion.
    auto activePlayer = game->getActivePlayer();
    auto& minions = activePlayer->getBoard()->getMinions();
    if (minions.empty()) return;
    auto newMinion = minions.back();
    activePlayer->getGraveyard()->addMinion(newMinion);
    activePlayer->getBoard()->removeMinion(minions.size() - 1);
    ritual->setCharges(ritual->getCharges() - 1);
    cout << "DEBUG: (TriggeredAbility) OnEnterDestroy: Destroyed newly entered minion, sent to graveyard." << endl;
}
bool OnEnterDestroy::shouldTrigger() const {
    return true;
}
