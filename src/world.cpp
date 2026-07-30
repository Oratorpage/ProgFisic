#include "world.hpp"

namespace bs {

World::World(WorldParams const& wp)
    : width_{wp.dimensions.x},
      height_{wp.dimensions.y},
      toroidal_{wp.toroidal} {};

double const& World::Width() const { return width_; }
double const& World::Height() const { return height_; }
bool const& World::Toroidal() const { return toroidal_; }

V2D const& World::Dimensions() const {
  return {width_, height_};
}  // Qua e per tutte le cose inerenti devo determinare la differenza tra
   // l'inizializzazione con () e con {}; devo andare a vedere la teoria che non
   // mi ricordo bene

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