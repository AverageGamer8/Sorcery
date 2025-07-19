#include "card.h"
using namespace std;

Card::Card(string name, string description, string type, int cost, int owner) :
    name{name}, description{description}, type{type}, cost{cost}, owner{owner} {}