#include "deck.h"
#include "minion.h"
#include <iostream>
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
            auto card = make_unique<AirElemental>(owner);
            cards.emplace_back(move(card));
        }
        else if (name == "Earth Elemental") {
            auto card = make_unique<EarthElemental>(owner);
            cards.emplace_back(move(card));
        }
        else if (name == "Fire Elemental") {
            auto card = make_unique<FireElemental>(owner);
            cards.emplace_back(move(card));
        }
        else if (name == "Potion Seller") {
            auto card = make_unique<PotionSeller>(owner);
            cards.emplace_back(move(card));
        }
        else if (name == "Novice Pyromancer") {
            auto card = make_unique<NovicePyromancer>(owner);
            cards.emplace_back(move(card));
        }
        else if (name == "Apprentice Summoner") {
            auto card = make_unique<ApprenticeSummoner>(owner);
            cards.emplace_back(move(card));
        }
        else if (name == "Master Summoner") {
            auto card = make_unique<MasterSummoner>(owner);
            cards.emplace_back(move(card));
        }
        // else if (name == "Banish") {
        //     auto card = make_unique<Banish>(owner);
        //     cards.emplace_back(move(card));
        // }
        // else if (name == "Unsummon") {
        //     auto card = make_unique<Unsummon>(owner);
        //     cards.emplace_back(move(card));
        // }
        // else if (name == "Recharge") {
        //     auto card = make_unique<Recharge>(owner);
        //     cards.emplace_back(move(card));
        // }
        // else if (name == "Disenchant") {
        //     auto card = make_unique<Disenchant>(owner);
        //     cards.emplace_back(move(card));
        // }
        // else if (name == "Raise Dead") {
        //     auto card = make_unique<RaiseDead>(owner);
        //     cards.emplace_back(move(card));
        // }
        // else if (name == "Blizzard") {
        //     auto card = make_unique<Blizzard>(owner);
        //     cards.emplace_back(move(card));
        // }
        // else if (name == "Giant Strength") {
        //     auto card = make_unique<GiantStrength>(owner);
        //     cards.emplace_back(move(card));
        // }
        // else if (name == "Magic Fatigue") {
        //     auto card = make_unique<MagicFatigue>(owner);
        //     cards.emplace_back(move(card));
        // }
        // else if (name == "Silence") {
        //     auto card = make_unique<Silence>(owner);
        //     cards.emplace_back(move(card));
        // }
        // else if (name == "Dark Ritual") {
        //     auto card = make_unique<DarkRitual>(owner);
        //     cards.emplace_back(move(card));
        // }
        // else if (name == "Aura of Power") {
        //     auto card = make_unique<AuraOfPower>(owner);
        //     cards.emplace_back(move(card));
        // }
        // else if (name == "Standstill") {
        //     auto card = make_unique<Standstill>(owner);
        //     cards.emplace_back(move(card));
        // }
    }
}

void Deck::shuffleDeck() {
    shuffle(cards.begin(), cards.end(), default_random_engine(seed));
}

void Deck::reSeed() {
    seed = chrono::system_clock::now().time_since_epoch().count();
}