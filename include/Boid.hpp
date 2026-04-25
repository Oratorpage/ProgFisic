// Specialized variable defining a singular element of the flock
#ifndef FLOCK_BOID_HPP
#define FLOCK_BOID_HPP

#include "V2D.hpp"

namespace flock {

class Boid {
 private:
  V2D velocity_{0., 0.};
  V2D position_{0., 0.};
  static constexpr double maxspeedtor{150.};
  static constexpr double maxspeed{300.};

 public:
  Boid(V2D v, V2D p);

  V2D const& Vel() const;
  V2D const& Pos() const;

  void update(double dt, V2D const& tsize, V2D const& vup,
              bool const& toroidal);
};

}  // namespace flock

#endif