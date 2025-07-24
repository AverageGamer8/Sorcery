#ifndef ARG_EXCEPTION_H
#define ARG_EXCEPTION_H

#include <stdexcept>
#include <string>

class ArgException : public std::runtime_error {
public:
    explicit ArgException(const std::string& error);
};

#endif