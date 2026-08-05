#ifndef BS_BEHAVIOUR_HPP
#define BS_BEHAVIOUR_HPP

#include <vector>

#include "boid.hpp"
#include "boidProperties.hpp"
#include "simulationParams.hpp"

namespace bs {
double distSq(V2D const& a, V2D const& b);
bool isBoidVisibleInCone(Boid const& a, Boid const& b,
                         BoidProperties const& boid_params);
std::vector<Boid*> collectVisibleBoids(std::vector<Boid>& flock,
                                       Boid const& bi, BoidProperties const& boid_params);
std::vector<Boid> applyFlockBehaviouralMovement(std::vector<Boid>& flock,
                                               double dt,
                                               BoidProperties const& boid_params);
}  // namespace bs

#endif