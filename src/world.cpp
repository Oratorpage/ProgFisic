#include "world.hpp"

namespace bs {

World::World(WorldParams const& wp)
    : width_{wp.dimensions.x},
      height_{wp.dimensions.y},
      toroidal_{wp.toroidal} {
        worldInvariant();
      };

void World::worldInvariant() {
  if (width_ <= 0) {
    throw std::invalid_argument(
        "world width value is not acceptable, cannot be less or equal to zero");
  }
  if (height_ <= 0) {
    throw std::invalid_argument(
        "world height value is not acceptable, cannot be less or equal to "
        "zero");
  }
}

double const& World::Width() const { return width_; }
double const& World::Height() const { return height_; }
bool const& World::Toroidal() const { return toroidal_; }
V2D const& World::Dimensions() const { return {width_, height_}; }

void World::wrap(std::vector<Boid> const& flock) {
  for (Boid b : flock) {
    if (b.Pos().x > width_) {
      b.pChange(width_ - b.Pos().x, true);
    }
    if (b.Pos().x < 0.) {
      b.pChange(width_, true);
    }
    if (b.Pos().y > height_) {
      b.pChange(height_ - b.Pos().y, false);
    }
    if (b.Pos().y < 0.) {
      b.pChange(height_, false);
    }
  };
}
}  // namespace bs