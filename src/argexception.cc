#include "argexception.h"

ArgException::ArgException(const std::string& error)
    : std::runtime_error(error) {}