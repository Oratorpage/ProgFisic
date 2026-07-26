#include "vChange.hpp"

#include <cmath>

namespace flock {

double distSq(V2D const& a, V2D const& b) {
  V2D d = a - b;
  return dotprod(d, d);
}

constexpr double valLim{1.e-12};
constexpr double piconst{3.14159265358979323846264338327950288};

bool isBoidVisibleInCone(Boid const& a, Boid const& b,
                         SimParams const& params) {
  if (&a == &b) {
    return false;
  }

  const double detection_rad_sq = params.detection_rad * params.detection_rad;
  if (distSq(a.Pos(), b.Pos()) > detection_rad_sq) {
    return false;
  }
  if (params.angle_of_view >= 360.) {
    return true;
  }

  // The vector of the velocity of the boid a, the one that gets compared
  // against all others, is the vector of the axis passing through a, based on
  // that and the vector of the distance with the other boid, i determinate the
  // angle
  const V2D vectVelA{a.Vel()};
  const V2D vectDistance{a.Pos() - b.Pos()};

  const double velANorm{norm(vectVelA)};
  const double distanceNorm{norm(vectDistance)};

  if (distanceNorm <= valLim) {
    return true;
  }
  const double cosHalfAngleView{
      std::cos(params.angle_of_view * 0.5 * piconst / 180.)};

  const double cosAngle{dotprod(vectVelA, vectDistance) / velANorm *
                        distanceNorm};

  if (cosAngle >= cosHalfAngleView && velANorm <= valLim) {
    return true;
  }
  return cosAngle >= cosHalfAngleView;
}

std::vector<Boid*> collectVisibleBoids(std::vector<Boid>& boids, Boid const& bi,
                                       SimParams const& params) {
  std::vector<Boid*> nearboids;
  nearboids.reserve(boids.size() -
                    1);  // Controlla se sensato, in teoria sì perchè quello
                         // contro cui faccio i check non viene aggiunto
  for (Boid& bj : boids) {
    if (isBoidVisibleInCone(bi, bj, params)) {
      nearboids.push_back(&bj);
    }
  }
  return nearboids;
}

void velocityChangeBoids(std::vector<Boid>& boids, double dt,
                         V2D const& flock_window_size_d,
                         SimParams const& params) {
  const double danger_rad_sq{params.danger_rad * params.danger_rad};

  for (Boid& bi : boids) {
    std::vector<Boid*> nearboids{collectVisibleBoids(boids, bi, params)};
    V2D separation_vel;
    V2D alignment_vel;
    V2D cm_pos;
    V2D cohesion_vel;

    // Loop that calculates vchange based on nearby boids
    if (!nearboids.empty()) {
      const double invNear = 1. / static_cast<double>(nearboids.size());

      for (Boid* bj : nearboids) {
        if (&bi == bj) {
          continue;
        }

        if (bi.IsPredator() && !(bj->IsPredator())) {
          separation_vel -= bj->Pos() - bi.Pos();
          cm_pos += bj->Pos();
        }

        if (!(bi.IsPredator()) && bj->IsPredator()) {
          separation_vel += (bj->Pos() - bi.Pos()) * 2.;
          alignment_vel -= bj->Vel();
          cm_pos -= bj->Pos();
        }

        if (bi.IsPredator() && bj->IsPredator()) {
          if (distSq(bi.Pos(), bj->Pos()) < danger_rad_sq) {
            separation_vel += bj->Pos() - bi.Pos();
          }
          alignment_vel += bj->Vel();
          cm_pos += bj->Pos();
        }

        if (!(bi.IsPredator()) && !(bj->IsPredator())) {
          if (distSq(bi.Pos(), bj->Pos()) < danger_rad_sq) {
            separation_vel += bj->Pos() - bi.Pos();
          }
          alignment_vel += bj->Vel();
          cm_pos += bj->Pos();
        }
      }
      separation_vel = -params.separation * separation_vel;
      alignment_vel = params.allignment * (invNear * alignment_vel - bi.Vel());
      cm_pos = invNear * cm_pos;
      cohesion_vel = params.cohesion * (cm_pos - bi.Pos());
    }
    // If there are no near boids it will update anyway but vup will be 0
    // because of the standard inizialization of the V2D
    V2D vup{separation_vel + alignment_vel + cohesion_vel};
    bi.update(dt, flock_window_size_d, vup, params.toroidal);
  }
}
}  // namespace flock