// Generate random position and velocity
#ifndef BS_RAND_HPP
#define BS_RAND_HPP

#include "v2D.hpp"

namespace bs {
V2D randVel(double const max_speed);
V2D randPos(V2D const& flock_window_size_d);
}  // namespace bs

#endif