#include "deck.h"
#include "card.h"
#include "player.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
using namespace std;

int main() {
    Deck deck(1);
    ifstream file{"../sorcery-asciiart/default.deck"};
    deck.loadDeck(file);
    file.close();

    Player player{"Bob", 20, 10};
    player.setDeck(deck);

    cout << "Original Deck:\n";
    for (const auto& card : player.getDeck()->getCards()) {
        cout << card->getName() << '\n';
    }

    player.getDeck()->shuffleDeck();
    cout << "\nAfter shuffle:\n";
    for (const auto& card : player.getDeck()->getCards()) {
        cout << card->getName() << '\n';
    }

    player.draw();
    cout << "\nDeck:\n";
    for (const auto& card : player.getDeck()->getCards()) {
        cout << "- " << card->getName() << '\n';
    }
    cout << "\nHand:\n";
    for (const auto& card : player.getHand()->getCards()) {
        cout << "- " << card->getName() << '\n';
    }
}