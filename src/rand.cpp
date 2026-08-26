#include "rand.hpp"

#include <random>

namespace bs {
std::random_device r;
std::mt19937 gen(r());

V2D randVel(double const max_speed) {
  // The parameter max_speed will always be positive so there won't be problems
  // with the interval of distribution; when this will be needed in a situation
  // where one cannot be certain of the sign prior to the function: this
  // function shall be changed to accomodate the needs, in a long long time, in
  // a distant galaxy
  std::uniform_real_distribution<> distrx(-max_speed, max_speed);
  std::uniform_real_distribution<> distry(-max_speed, max_speed);
  return V2D{distrx(gen), distry(gen)};
}

V2D randPos(V2D const& world_dimensions) {
  // Same goes here
  std::uniform_real_distribution<> distrx(0, world_dimensions.x);
  std::uniform_real_distribution<> distry(0, world_dimensions.y);
  return V2D{distrx(gen), distry(gen)};
}

}  // namespace bs