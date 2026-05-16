//Makes it possible to read the parameters
#ifndef FLOCK_INPUT_HPP
#define FLOCK_INPUT_HPP

#include "simParams.hpp"
#include <string>

namespace flock{
    std::string trimSpaces(std::string line);

    int parseInt(std::string const& string_value);
    double parseDouble(std::string const& string_value);
    bool parseBool(std::string const& string_value);

    SimParams readFileParams(std::string const& path);
}

#endif