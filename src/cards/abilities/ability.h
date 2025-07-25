#ifndef ABILITY_H
#define ABILITY_H

#include <string>

using namespace std;

class Ability {
   public:
    std::string desc;

    Ability(const string& desc) : desc{desc} {}
    virtual bool activate() = 0;
    virtual ~Ability() = default;

    virtual string getDesc() const { return desc; }
};

#endif
