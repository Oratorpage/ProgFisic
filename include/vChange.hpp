#ifndef FLOCK_VCHANGE_HPP
#define FLOCK_VCHANGE_HPP

#include <vector>

#include "boid.hpp"
#include "simParams.hpp"

namespace flock {
double distSq(V2D const& a, V2D const& b);
bool isBoidVisibleInCone(Boid const& a, Boid const& b, SimParams const& params);
std::vector<Boid*> collectVisibleBoids(std::vector<Boid>& boids, Boid const& bi,
                                       SimParams const& params);
void velocityChangeBoids(std::vector<Boid>& Boids, double dt,
                         V2D const& flock_window_size_d,
                         SimParams const& params);
}  // namespace flock

#endif