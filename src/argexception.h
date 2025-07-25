#ifndef ARG_EXCEPTION_H
#define ARG_EXCEPTION_H

#include <exception>
#include <string>
using namespace std;

class ArgException : public exception {
    string message = "Error: ";

   public:
    explicit ArgException(const string& error);
    const char* what();
};

#endif