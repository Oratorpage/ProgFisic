#include "rand.hpp"

#include <random>

namespace flock {
std::random_device r;
std::mt19937 gen(r());

V2D randVel() {
  std::uniform_real_distribution<> distrx(-25, 25);
  std::uniform_real_distribution<> distry(-25, 25);
  return V2D{distrx(gen), distry(gen)};
}

V2D randPos(V2D const& flock_window_size_d) {
  std::uniform_real_distribution<> distrx(0, flock_window_size_d.x);
  std::uniform_real_distribution<> distry(0, flock_window_size_d.y);
  return V2D{distrx(gen), distry(gen)};
}

}  // namespace flock