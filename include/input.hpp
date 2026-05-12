//Makes it possible to read the parameters
#ifndef FLOCK_INPUT_HPP
#define FLOCK_INPUT_HPP

#include "simParams.hpp"
#include <string>

namespace flock{
    SimParams readFileParams(std::string const& path);
}

#endif