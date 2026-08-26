#include "world.hpp"

namespace bs {

World::World(WorldParams const& wp)
    : width_{wp.dimensions.x},
      height_{wp.dimensions.y},
      dimensions_{wp.dimensions},
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

double const& World::getWidth() const { return width_; }
double const& World::getHeight() const { return height_; }
bool const& World::isToroidal() const { return toroidal_; }
V2D const& World::getDimensions() const { return dimensions_; }

void World::wrap(std::vector<Boid>& flock) {
  for (Boid& b : flock) {
    if (b.Pos().x > width_) {
      b.setPosition(0., true);
    }
    if (b.Pos().x < 0.) {
      b.setPosition(width_, true);
    }
    if (b.Pos().y > height_) {
      b.setPosition(0., false);
    }
    if (b.Pos().y < 0.) {
      b.setPosition(height_, false);
    }
  };
}

void World::contain(std::vector<Boid>& flock, BoidProperties const& bp) {
  for (Boid& b : flock) {
    V2D vel_update{};
    vel_update = resultVel(b, bp);
    b.vUpdate(vel_update);
  }
}

V2D World::resultVel(Boid const& boid, BoidProperties const& bp) {
  V2D p{boid.Pos()};
  V2D v{boid.Vel()};
  double lim_x{width_ - 15.};
  double lim_y{height_ - 15.};

  V2D resuling_velocity{0., 0.};

  if (p.x > lim_x) {
    resuling_velocity.x +=
        -(bp.max_speed / (width_ - p.x) + 2. * v.x / bp.max_speed);
  }
  if (p.x < 15.) {
    resuling_velocity.x += bp.max_speed / p.x - 2. * v.x / bp.max_speed;
  }
  if (p.y > lim_y) {
    resuling_velocity.y +=
        -(bp.max_speed / (height_ - p.y) + 2. * v.y / bp.max_speed);
  }
  if (p.y < 15.) {
    resuling_velocity.y += bp.max_speed / p.y - 2. * v.y / bp.max_speed;
  }
  return resuling_velocity;
}

}  // namespace bs