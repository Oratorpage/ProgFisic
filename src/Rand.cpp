#include "Rand.hpp"

#include <random>

namespace flock {
std::random_device r;
std::mt19937 gen(r());

V2D randvel() {
  std::uniform_real_distribution<> distrx(-25, 25);
  std::uniform_real_distribution<> distry(-25, 25);
  return V2D{distrx(gen), distry(gen)};
}

V2D randpos(V2D const& fwstsize) {
  std::uniform_real_distribution<> distrx(0, fwstsize.x);
  std::uniform_real_distribution<> distry(0, fwstsize.y);
  return V2D{distrx(gen), distry(gen)};
}

}  // namespace flock