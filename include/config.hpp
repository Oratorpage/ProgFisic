#ifndef BS_CONFIG_HPP
#define BS_CONDIG_HPP

#include "renderParams.hpp"
#include "simulationParams.hpp"
#include "worldParams.hpp"
#include "boidProperties.hpp"

namespace bs {
struct Config {
  SimParams sp;
  RenParams rp;
  WorldParams wp;
  BoidProperties bp;
};
}  // namespace bs

#endif