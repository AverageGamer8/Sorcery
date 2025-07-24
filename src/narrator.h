#ifndef NARRATOR_H
#define NARRATOR_H

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

const int delayMs = 150;
const int charsToDelay = 5;

class Narrator {
private:
    static bool enabled;
    static bool delayed;
    
public:
    static void setEnabled(bool enable);
    static void setDelayed(bool delay);
    static void printLine();
    static void announce(const std::string& message);
};

#endif