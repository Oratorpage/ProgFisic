// Specialized variable defining a singular element of the flock
#ifndef FLOCK_BOID_HPP
#define FLOCK_BOID_HPP

#include "V2D.hpp"
#include <stdexcept>

namespace flock {

class Boid {
 private:
  V2D velocity_{0., 0.};
  V2D position_{0., 0.};
  static constexpr double max_speed_tor{150.};
  static constexpr double max_speed{250.};
  bool is_predator_{false};

 public:
  Boid();
  Boid(V2D v, V2D p);
  Boid(V2D v, V2D p, bool is_predator);

  V2D const& Vel() const;
  V2D const& Pos() const;
  bool IsPred() const;

  void update(double dt, V2D const& flock_window_size, V2D const& vel_update,
              bool const& toroidal);
};

}  // namespace flock

#endif