#include "Boid.hpp"

namespace flock {

Boid::Boid() = default;
Boid::Boid(V2D v, V2D p) : velocity_{v}, position_{p} {}
Boid::Boid(V2D v, V2D p, bool is_predator)
    : velocity_{v}, position_{p}, is_predator_{is_predator} {}

V2D const& Boid::Vel() const { return velocity_; }
V2D const& Boid::Pos() const { return position_; }
bool Boid::IsPred() const { return is_predator_; }

void Boid::update(double dt, V2D const& flock_window_size,
                  V2D const& vel_update, bool const& toroidal) {
  if (dt > 0.5) {
    throw std::runtime_error{"dt is too big"};
  }
  velocity_ += vel_update * dt;
  position_ += velocity_ * dt;
  if (toroidal) {
    if (position_.x < 0) {
      position_.x = flock_window_size.x;
    }
    if (position_.y < 0) {
      position_.y = flock_window_size.y;
    }
    if (position_.x > flock_window_size.x) {
      position_.x = 0.;
    }
    if (position_.y > flock_window_size.y) {
      position_.y = 0.;
    }
    // Velocity constraint for the toroidal space, avoids particle
    // accellerator behaviour
    if (velocity_.x > max_speed_tor) {
      velocity_.x = max_speed_tor;
    }
    if (velocity_.x < -max_speed_tor) {
      velocity_.x = -max_speed_tor;
    }
    if (velocity_.y > max_speed_tor) {
      velocity_.y = max_speed_tor;
    }
    if (velocity_.y < -max_speed_tor) {
      velocity_.y = -max_speed_tor;
    }
  } else {
    // A non-toroidal space shouldn't need a velocity limiter, it is built in
    if (position_.x < 20) {
      velocity_.x += 10.;
    }
    if (position_.y < 20) {
      velocity_.y += 10.;
    }
    if (position_.x > flock_window_size.x - 20) {
      velocity_.x -= 10.;
    }
    if (position_.y > flock_window_size.y - 20) {
      velocity_.y -= 10.;
    }
    // unfortunately for extreme parameters it needs an additional constraint
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
}

}  // namespace flock
