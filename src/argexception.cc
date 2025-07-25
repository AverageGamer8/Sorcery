#include "argexception.h"
using namespace std;

ArgException::ArgException(const string& error) {
    message += error;
}
const char* ArgException::what() {
    return message.c_str();
}
