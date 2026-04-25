#include "VChange.hpp"
// forse devi includere anche vector, anche se è già incluso nell'hpp dunque non
// so

namespace flock {

double distSq(V2D const& a, V2D const& b) {
  double dx{a.x - b.x};
  double dy{a.y - b.y};
  return dx * dx + dy * dy;
}

void VChangeBoids(std::vector<Boid>& Boids, double dt, V2D const& fwstsize,
                  SimParams const& params) {
  const double detectradsq{params.detectrad * params.detectrad};
  const double dangerradsq{params.dangerrad * params.dangerrad};
  for (auto& bi : Boids) {
    std::vector<Boid*> nearboids;
    V2D vsep;
    V2D vallig;
    V2D xcm;
    V2D vcoes;
    // Creating a neighbouring boids vector* to calculate vchange based on near
    // boids
    for (auto& bj : Boids) {
      if (&bi != &bj && distSq(bi.Pos(), bj.Pos()) < detectradsq) {
        nearboids.push_back(&bj);
      }
    }
    // Loop that calculates vchange based on nearby boids
    if (!nearboids.empty()) {
      double invNear = 1. / static_cast<double>(nearboids.size());
      for (auto& bj : nearboids) {
        if (&bi != bj) {
          if (distSq(bi.Pos(), bj->Pos()) < dangerradsq) {
            vsep += bj->Pos() - bi.Pos();
          }
          vallig += bj->Vel();
          xcm += bj->Pos();
        }
      }
      vsep = -params.s * vsep;
      vallig = params.a * (invNear * vallig - bi.Vel());
      xcm = invNear * xcm;
      vcoes = params.c * (xcm - bi.Pos());
    }
    V2D vup = vsep + vallig + vcoes;
    bi.update(dt, fwstsize, vup, params.toroidal);
  }
}
}  // namespace flock