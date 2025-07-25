#include "card.h"
using namespace std;

Card::Card(string name, string description, string type, int cost, int owner, Game* game) :
    name{name}, description{description}, type{type}, cost{cost}, owner{owner}, game{game} {}
    