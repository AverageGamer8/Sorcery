#include "triggeredability.h"
#include "./gameModel/game.h"
#include <memory>
using namespace std;

void TriggeredAbility::notify() { activate(); }

OnStartGainMagic::OnStartGainMagic(shared_ptr<Game> game) : TriggeredAbility{game} {}
void OnStartGainMagic::activate() {
    return;
}

OnEnterBuff::OnEnterBuff(shared_ptr<Game> game) : TriggeredAbility{game} {}
void OnEnterBuff::activate() {
    return;
}

OnEnterDestroy::OnEnterDestroy(shared_ptr<Game> game) : TriggeredAbility{game} {}
void OnEnterDestroy::activate() {
    return;
}
