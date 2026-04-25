#include "Boid.hpp"

namespace flock {

  Boid::Boid(V2D v, V2D p) : velocity_{v}, position_{p} {}
  
  V2D const& Boid::Vel() const { return velocity_; }
  V2D const& Boid::Pos() const { return position_; }

  
  void Boid::update(double dt, V2D const& tsize, V2D const& vup,
              bool const& toroidal) {
    velocity_ += vup * dt;
    position_ += velocity_ * dt;
    if (toroidal) {
      if (position_.x < 0) {
        position_.x = tsize.x;
      }
      if (position_.y < 0) {
        position_.y = tsize.y;
      }
      if (position_.x > tsize.x) {
        position_.x = 0.;
      }
      if (position_.y > tsize.y) {
        position_.y = 0.;
      }
      // Velocity constraint for the toroidal space, avoids particle
      // accellerator behaviour
      if (velocity_.x > maxspeedtor) {
        velocity_.x = maxspeedtor;
      }
      if (velocity_.x < -maxspeedtor) {
        velocity_.x = -maxspeedtor;
      }
      if (velocity_.y > maxspeedtor) {
        velocity_.y = maxspeedtor;
      }
      if (velocity_.y < -maxspeedtor) {
        velocity_.y = -maxspeedtor;
      }
    } else {
      // A non-toroidal space shouldn't need a velocity limiter, it is built in
      if (position_.x < 20) {
        velocity_.x += 10.;
      }
      if (position_.y < 20) {
        velocity_.y += 10.;
      }
      if (position_.x > tsize.x - 20) {
        velocity_.x -= 10.;
      }
      if (position_.y > tsize.y - 20) {
        velocity_.y -= 10.;
      }
      // unfortunately for extreme parameters it needs an additional constraint
      if (velocity_.x > maxspeed) {
        velocity_.x = maxspeed;
      }
      if (velocity_.x < -maxspeed) {
        velocity_.x = -maxspeed;
      }
      if (velocity_.y > maxspeed) {
        velocity_.y = maxspeed;
      }
      if (velocity_.y < -maxspeed) {
        velocity_.y = -maxspeed;
      }
    }
  }


}  // namespace flock

