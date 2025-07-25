#include "utils.h"

#include <iostream>
using namespace std;

bool parseInt(const string& s, int& res) {
    try {
        res = stoi(s);
        return true;
    } catch (...) {
        cerr << "Invalid Input: Invalid integer." << endl;
        return false;
    }
}
