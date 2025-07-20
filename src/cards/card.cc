#include "card.h"
using namespace std;

Card::Card(string name, string description, string type, int cost, int owner, shared_ptr<Game> game) :
    name{name}, description{description}, type{type}, cost{cost}, owner{owner}, game{game} {}