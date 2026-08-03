#include "boid.hpp"

namespace bs {

Boid::Boid(V2D const& v, V2D const& p, bool is_predator)
    : velocity_{v}, position_{p}, is_predator_{is_predator} {}

V2D const& Boid::Vel() const { return velocity_; }
V2D const& Boid::Pos() const { return position_; }
bool Boid::IsPredator() const { return is_predator_; }

void Boid::update(V2D const& vel_update, double dt) {
  
  velocity_ += vel_update * dt;
  position_ += velocity_ * dt;
}

void Boid::pChange(double value, bool x){
  if(x == true){
    position_.x = value;
  } else {
    position_.y = value;
  }
}

}  // namespace bs
