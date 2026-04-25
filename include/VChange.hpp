#ifndef FLOCK_VCHANGE_HPP
#define FLOCK_VCHANGE_HPP

#include <vector>

#include "Boid.hpp"
#include "SimParams.hpp"

namespace flock {
void VChangeBoids(std::vector<Boid>& Boids, double dt, V2D const& fwstsize,
                  SimParams const& params);
}

#endif