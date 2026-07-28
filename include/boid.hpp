// Specialized variable defining a singular element of the flock
#ifndef BS_BOID_HPP
#define BS_BOID_HPP

#include "v2D.hpp"
#include <stdexcept>

namespace bs {

class Boid {
 private:
  V2D velocity_{0., 0.};
  V2D position_{0., 0.};
  static constexpr double max_speed_tor{150.}; // La velocità la posso limitare tramite una funzione magari, vedo com'è il limiter all'interno, forse è meno efficente, però effettivamente sarebbe bello avere un'opzione limiter off e semplicemente vedere il caos
  static constexpr double max_speed{250.};
  bool is_predator_{false};

 public:
  Boid();
  Boid(V2D const& v, V2D const& p);
  Boid(V2D const& v, V2D const& p, bool is_predator);

  V2D const& Vel() const;
  V2D const& Pos() const;
  bool IsPredator() const;

  void update(double dt, V2D const& flock_window_size, V2D const& vel_update,
              bool toroidal);
};

}  // namespace bs

#endif