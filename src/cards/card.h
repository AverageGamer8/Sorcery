#ifndef CARD_H
#define CARD_H

#include <memory>
#include <string>
using namespace std;

class Game;

class Card {
    protected:
        string name;
        string description;
        string type;
        int cost;
        int owner;
        Game* game;

    public:
        Card(string name, string description, string type, int cost, int owner, Game* game);
        virtual string getName() const = 0;
        virtual string getDesc() const = 0;
        virtual string getType() const = 0;
        virtual int getCost() const = 0;

        virtual ~Card() = default;
};

#endif
