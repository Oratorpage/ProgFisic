#include "rand.hpp"

#include <random>

namespace bs {
std::random_device r;
std::mt19937 gen(r());

V2D randVel(double const min_speed, double const max_speed) {
  std::uniform_real_distribution<> distrx(-min_speed, max_speed);
  std::uniform_real_distribution<> distry(-min_speed, max_speed);
  return V2D{distrx(gen), distry(gen)};
}

V2D randPos(V2D const& flock_window_size_d) {
  std::uniform_real_distribution<> distrx(0, flock_window_size_d.x);
  std::uniform_real_distribution<> distry(0, flock_window_size_d.y);
  return V2D{distrx(gen), distry(gen)};
}

}  // namespace bs