// Generate random position and velocity
#ifndef FLOCK_RAND_HPP
#define FLOCK_RAND_HPP

#include "V2D.hpp"

namespace flock {
V2D randvel();
V2D randpos(V2D const& fwstsize);
}  // namespace flock

#endif