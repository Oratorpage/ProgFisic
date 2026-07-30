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
  Boid();
  Boid(V2D const& v, V2D const& p);
  Boid(V2D const& v, V2D const& p, bool is_predator);

  V2D const& Vel() const;
  V2D const& Pos() const;
  bool IsPredator() const;

  // La funzione di update deve solo fare l'update, il tempo è controllato da
  // conductor che sincronizza render e simulation, il calcolo della velocità
  // quando è toroidale anche; l'unica cosa scomoda che poi capirò come fare è
  // il wrap per quando è toroidale ma onestamente quello lo posso relegare a
  // World, come funzione membro, wrap tale che prende il flock, itera su di
  // esso ed in base alla distanza in più rispetto ai bordi del mondo gli fa
  // fare il wrap
  void update(V2D const& vel_update);
  void pChange(double value, bool x);
};

}  // namespace bs

#endif