// Specialized variable defining a singular element of the flock
#ifndef BS_BOID_HPP
#define BS_BOID_HPP

#include <stdexcept>

#include "v2D.hpp"

namespace bs {

class Boid {
 private:
  V2D velocity_{0., 0.};
  V2D position_{0., 0.};
  bool is_predator_{false};

 public:
  Boid(V2D const& v, V2D const& p, bool is_predator);

  V2D const& Vel() const;
  V2D const& Pos() const;
  bool IsPredator() const;

  

  void completeUpdate(V2D const& vel_update, double dt);
  void vUpdate(V2D const& vel_update);
  void setPosition(double value, bool x);
  void limitVelocity(double const max_speed, double const min_speed);
};

}  // namespace bs

#endif