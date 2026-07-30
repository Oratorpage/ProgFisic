#ifndef BS_WORLD_HPP
#define BS_WORLD_HPP

#include <vector>

#include "boid.hpp"
#include "worldParams.hpp"

namespace bs {
class World {
 private:
  double width_{};
  double height_{};
  bool toroidal_{};

 public:
  World(WorldParams const& wp);

  double const& Width() const;
  double const& Height() const;
  bool const& Toroidal() const;
  V2D const& Dimensions() const;
  // Non so se in realtà sia il modo migliore per passarglielo, adesso vedo,
  // quando poi dovrò farlo
  void wrap(std::vector<Boid> const& flock);
};
}  // namespace bs

#endif