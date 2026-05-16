#ifndef FLOCK_VCHANGE_HPP
#define FLOCK_VCHANGE_HPP

#include <vector>

#include "boid.hpp"
#include "simParams.hpp"

namespace flock {
double angleDist();
double distSq(V2D const& a, V2D const& b);
void velocityChangeBoids(std::vector<Boid>& Boids, double dt, V2D const& flock_window_size_d,
                  SimParams const& params);
}

#endif