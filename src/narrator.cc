#include "narrator.h"

bool Narrator::enabled = false;
bool Narrator::delayed = false;

void Narrator::setEnabled(bool enable) {
    enabled = enable;
}

void Narrator::setDelayed(bool delay) {
    delayed = delay;
}

void Narrator::printLine() {
    if (!enabled) return;

    std::string line = "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~";
    for (char c : line) {
        std::cout << c << std::flush;
        if (delayed) {
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMs / 20));
        }
    }
    std::cout << std::endl;
}

void Narrator::announce(const std::string& message) {
    if (!enabled) return;

    std::cout << "Narrator: ";
    for (size_t i = 0; i < message.size(); ++i) {
        std::cout << message[i] << std::flush;
        if (delayed) {
            int delay = (i < charsToDelay) ? delayMs : delayMs / charsToDelay;
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
    }
    std::cout << std::endl;
}