#include "deck.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

Deck::Deck(int player) : player{player}, seed{chrono::system_clock::now().time_since_epoch().count()} {}

void Deck::loadDeck(ifstream& inf) {
    string name;

    while (getline(inf, name)) {
        auto card;
        if (name == "Air Elemental") {
            card = make_unique<AirElemental>(player);
        }
        else if (name == "Earth Elemental") {
            card = make_unique<EarthElemental>(player);
        }
        else if (name == "Fire Elemental") {
            card = make_unique<FireElemental>(player);
        }
        else if (name == "Potion Seller") {
            card = make_unique<PotionSeller>(player);
        }
        else if (name == "Novice Pyromancer") {
            card = make_unique<NovicePyromancer>(player);
        }
        else if (name == "Apprentice Summoner") {
            card = make_unique<ApprenticeSummoner>(player);
        }
        else if (name == "Master Summoner") {
            card = make_unique<MasterSummoner>(player);
        }
        else if (name == "Banish") {
            card = make_unique<Banish>(player);
        }
        else if (name == "Unsummon") {
            card = make_unique<Unsummon>(player);
        }
        else if (name == "Recharge") {
            card = make_unique<Recharge>(player);
        }
        else if (name == "Disenchant") {
            card = make_unique<Disenchant>(player);
        }
        else if (name == "Raise Dead") {
            card = make_unique<RaiseDead>(player);
        }
        else if (name == "Blizzard") {
            card = make_unique<Blizzard>(player);
        }
        else if (name == "Giant Strength") {
            card = make_unique<GiantStrength>(player);
        }
        else if (name == "Magic Fatigue") {
            card = make_unique<MagicFatigue>(player);
        }
        else if (name == "Silence") {
            card = make_unique<Silence>(player);
        }
        else if (name == "Dark Ritual") {
            card = make_unique<DarkRitual>(player);
        }
        else if (name == "Aura of Power") {
            card = make_unique<AuraOfPower>(player);
        }
        else if (name == "Standstill") {
            card = make_unique<Standstill>(player);
        }

        cards.emplace_back(card);
    }
}

void Deck::shuffleDeck() {
    shuffle(cards.begin(), cards.end(), default_random_engine(seed));
}

void Deck::reSeed() {
    seed = chrono::system_clock::now().time_since_epoch().count();
}