// Generate random position and velocity
#ifndef FLOCK_RAND_HPP
#define FLOCK_RAND_HPP

#include "V2D.hpp"

namespace flock {
V2D randVel();
V2D randPos(V2D const& flock_window_size_d);
}  // namespace flock

#endif