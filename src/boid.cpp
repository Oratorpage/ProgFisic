#include "boid.hpp"

namespace bs {

Boid::Boid(V2D const& v, V2D const& p, bool is_predator)
    : velocity_{v}, position_{p}, is_predator_{is_predator} {}

V2D const& Boid::Vel() const { return velocity_; }
V2D const& Boid::Pos() const { return position_; }
bool Boid::IsPredator() const { return is_predator_; }

void Boid::update(V2D const& vel_update, double dt) {
  velocity_ += vel_update;
  position_ += velocity_ * dt;
}

void Boid::vUpdate(V2D const& vel_update){
  velocity_ += vel_update;
}

void Boid::pChange(double value, bool x) {
  if (x == true) {
    position_.x = value;
  } else {
    position_.y = value;
  }
}

// Così però lungo le diagonali vanno più veloci, dovrei fare if velocity_sq >
// max_speed sq
void Boid::limitVelocity(double const max_speed) {
  if (velocity_.x > max_speed) {
    velocity_.x = max_speed;
  }
  if (velocity_.x < -max_speed) {
    velocity_.x = -max_speed;
  }
  if (velocity_.y > max_speed) {
    velocity_.y = max_speed;
  }
  if (velocity_.y < -max_speed) {
    velocity_.y = -max_speed;
  }
}

}  // namespace bs
