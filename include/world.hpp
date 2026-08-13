#ifndef BS_WORLD_HPP
#define BS_WORLD_HPP

#include <vector>

#include "boid.hpp"
#include "boidProperties.hpp"
#include "worldParams.hpp"

namespace bs {
class World {
 private:
  double width_{800};
  double height_{600};
  V2D dimensions_{800,600};
  bool toroidal_{false};

  void worldInvariant();

 public:
  World(WorldParams const& wp);

  double const& getWidth() const;
  double const& getHeight() const;
  bool const& isToroidal() const;
  V2D const& getDimensions() const;
  
  void wrap(std::vector<Boid>& flock);
  void contain(std::vector<Boid>& flock, BoidProperties const& bp);

  V2D resultVel(Boid const& boid, BoidProperties const& bp);
};
}  // namespace bs

#endif