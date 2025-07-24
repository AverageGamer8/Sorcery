#include "deck.h"
#include "../cards/minion.h"
#include "../cards/spell.h"
#include "../cards/ritual.h"
#include "../cards/enchantment.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <utility>
using namespace std;

Deck::Deck(int owner) : owner{owner}, seed{chrono::system_clock::now().time_since_epoch().count()} {}

void Deck::loadDeck(ifstream& inf, Game* game) {
    string name;
    while (getline(inf, name)) {
        if (name == "Air Elemental") {
            auto card = make_shared<AirElemental>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Earth Elemental") {
            auto card = make_shared<EarthElemental>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Bone Golem") {
            auto card = make_shared<BoneGolem>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Fire Elemental") {
            auto card = make_shared<FireElemental>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Potion Seller") {
            auto card = make_shared<PotionSeller>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Novice Pyromancer") {
            auto card = make_shared<NovicePyromancer>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Apprentice Summoner") {
            auto card = make_shared<ApprenticeSummoner>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Master Summoner") {
            auto card = make_shared<MasterSummoner>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Banish") {
            auto card = make_shared<Banish>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Unsummon") {
            auto card = make_shared<Unsummon>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Recharge") {
            auto card = make_shared<Recharge>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Disenchant") {
            auto card = make_shared<Disenchant>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Raise Dead") {
            auto card = make_shared<RaiseDead>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Blizzard") {
            auto card = make_shared<Blizzard>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Giant Strength") {
            auto card = make_shared<GiantStrength>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Enrage") {
            auto card = make_shared<Enrage>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Haste") {
            auto card = make_shared<Haste>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Magic Fatigue") {
            auto card = make_shared<MagicFatigue>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Silence") {
            auto card = make_shared<Silence>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Dark Ritual") {
            auto card = make_shared<DarkRitual>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Aura of Power") {
            auto card = make_shared<AuraOfPower>(owner, game);
            cards.emplace(cards.begin(), card);
        }
        else if (name == "Standstill") {
            auto card = make_shared<Standstill>(owner,game);
            cards.emplace(cards.begin(), card);
        }
    }
}

void Deck::shuffleDeck() {
    shuffle(cards.begin(), cards.end(), default_random_engine(seed));
}

vector<shared_ptr<Card>>& Deck::getCards() {
    return cards;
}

shared_ptr<Card> Deck::popTopCard() {
    if (cards.empty()) return nullptr; // TODO: exception.
    auto card = cards.back();
    cards.pop_back();
    return card;
}
