#ifndef BS_CONFIG_HPP
#define BS_CONDIG_HPP

#include "simulationParams.hpp"
#include "renderParams.hpp"

namespace bs{
    struct Config{
        SimParams sp;
        RenParams rp;
    };
}

#endif