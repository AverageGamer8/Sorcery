#include "deck.h"
#include "../cards/minion.h"
#include "../cards/spell.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <utility>
using namespace std;

Deck::Deck(int owner) : owner{owner}, seed{chrono::system_clock::now().time_since_epoch().count()} {}

void Deck::loadDeck(ifstream& inf) {
    string name;
    while (getline(inf, name)) {
        if (name == "Air Elemental") {
            auto card = make_shared<AirElemental>(owner);
            cards.emplace_back(card);
        }
        else if (name == "Earth Elemental") {
            auto card = make_shared<EarthElemental>(owner);
            cards.emplace_back(card);
        }
        else if (name == "Fire Elemental") {
            auto card = make_shared<FireElemental>(owner);
            cards.emplace_back(card);
        }
        else if (name == "Potion Seller") {
            auto card = make_shared<PotionSeller>(owner);
            cards.emplace_back(card);
        }
        else if (name == "Novice Pyromancer") {
            auto card = make_shared<NovicePyromancer>(owner);
            cards.emplace_back(card);
        }
        else if (name == "Apprentice Summoner") {
            auto card = make_shared<ApprenticeSummoner>(owner);
            cards.emplace_back(card);
        }
        else if (name == "Master Summoner") {
            auto card = make_shared<MasterSummoner>(owner);
            cards.emplace_back(card);
        }
        else if (name == "Banish") {
            auto card = make_shared<Banish>(owner);
            cards.emplace_back(card);
        }
        else if (name == "Unsummon") {
            auto card = make_shared<Unsummon>(owner);
            cards.emplace_back(card);
        }
        else if (name == "Recharge") {
            auto card = make_shared<Recharge>(owner);
            cards.emplace_back(card);
        }
        else if (name == "Disenchant") {
            auto card = make_shared<Disenchant>(owner);
            cards.emplace_back(card);
        }
        else if (name == "Raise Dead") {
            auto card = make_shared<RaiseDead>(owner);
            cards.emplace_back(card);
        }
        else if (name == "Blizzard") {
            auto card = make_shared<Blizzard>(owner);
            cards.emplace_back(card);
        }
        // else if (name == "Giant Strength") {
        //     auto card = make_shared<GiantStrength>(owner);
        //     cards.emplace_back(card);
        // }
        // else if (name == "Magic Fatigue") {
        //     auto card = make_shared<MagicFatigue>(owner);
        //     cards.emplace_back(card);
        // }
        // else if (name == "Silence") {
        //     auto card = make_shared<Silence>(owner);
        //     cards.emplace_back(card);
        // }
        // else if (name == "Dark Ritual") {
        //     auto card = make_shared<DarkRitual>(owner);
        //     cards.emplace_back(card);
        // }
        // else if (name == "Aura of Power") {
        //     auto card = make_shared<AuraOfPower>(owner);
        //     cards.emplace_back(card);
        // }
        // else if (name == "Standstill") {
        //     auto card = make_shared<Standstill>(owner);
        //     cards.emplace_back(card);
        // }
    }
}

void Deck::shuffleDeck() {
    shuffle(cards.begin(), cards.end(), default_random_engine(seed));
}

vector<shared_ptr<Card>>& Deck::getCards() {
    return cards;
}

shared_ptr<Card>& Deck::getTopCard() {
    return cards.back();
}

void Deck::popTopCard() {
    cards.pop_back();
}
