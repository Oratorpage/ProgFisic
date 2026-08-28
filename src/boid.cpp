#include "boid.hpp"

namespace bs {

Boid::Boid(V2D const& v, V2D const& p, bool is_predator)
    : velocity_{v}, position_{p}, is_predator_{is_predator} {}

V2D const& Boid::Vel() const { return velocity_; }
V2D const& Boid::Pos() const { return position_; }
bool Boid::IsPredator() const { return is_predator_; }

void Boid::setPosition(double value, bool x) {
  if (x == true) {
    position_.x = value;
  } else if (x == false) {
    position_.y = value;
  }
}

void Boid::completeUpdate(V2D const& vel_update, double const dt,
                          double const max_speed, double const min_speed) {
  velocity_ += vel_update;
  limitVelocity(max_speed, min_speed);
  position_ += velocity_ * dt;
}
void Boid::vUpdate(V2D const& vel_update) { velocity_ += vel_update; }

void Boid::limitVelocity(double const max_speed, double const min_speed) {
  double velocity_s{dotprod(velocity_, velocity_)};

  if (velocity_s > 0.) {
    if (velocity_s > max_speed * max_speed) {
      velocity_ *= max_speed / norm(velocity_);
    }
    if (velocity_s < min_speed * min_speed) {
      velocity_ *= min_speed / norm(velocity_);
    }
  }
}

}  // namespace bs
