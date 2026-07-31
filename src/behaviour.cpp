#include "behaviour.hpp"

#include <cmath>

namespace bs {

double distSq(V2D const& a, V2D const& b) {
  V2D d = a - b;
  return dotprod(d, d);
}

constexpr double valLim{1.e-12};
constexpr double piconst{3.14159265358979323846264338327950288};

bool isBoidVisibleInCone(Boid const& a, Boid const& b,
                         BoidProperties const& boid_params) {
  if (&a == &b) {
    return false;
  }

  const double detection_rad_sq =
      boid_params.detection_radius * boid_params.detection_radius;
  if (distSq(a.Pos(), b.Pos()) > detection_rad_sq) {
    return false;
  }
  if (boid_params.angle_of_view >= 360.) {
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
      std::cos(boid_params.angle_of_view * 0.5 * piconst / 180.)};

  const double cosAngle{dotprod(vectVelA, vectDistance) / velANorm *
                        distanceNorm};

  if (cosAngle >= cosHalfAngleView && velANorm <= valLim) {
    return true;
  }
  return cosAngle >= cosHalfAngleView;
}

std::vector<Boid*> collectVisibleBoids(std::vector<Boid> const& flock,
                                       Boid const& bi,
                                       BoidProperties const& boid_params) {
  std::vector<Boid*> nearboids;

  nearboids.reserve(flock.size() -
                    1);  // Controlla se sensato, in teoria sì perchè quello
                         // contro cui faccio i check non viene aggiunto
  for (Boid const& bj : flock) {
    if (isBoidVisibleInCone(bi, bj, boid_params)) {
      nearboids.emplace_back(&bj);
    }
  }
  return nearboids;
}

std::vector<Boid> applyFlockBehaviouralMovement(
    std::vector<Boid> const& flock, double dt,
    BoidProperties const& boid_params) {
  std::vector<Boid> buffer{flock};

  const double danger_rad_sq{boid_params.danger_radius *
                             boid_params.danger_radius};

  for (Boid const& bi : flock) {
    std::vector<Boid*> nearboids{collectVisibleBoids(buffer, bi, boid_params)};

    Boid buffer_boid{bi};
    V2D separation_vel;
    V2D alignment_vel;
    V2D cohesion_vel;

    V2D cm_pos;

    // Imma fix allthis after my run, peace

    // Loop that calculates vchange based on nearby boids
    if (!nearboids.empty()) {
      const double invNear = 1. / static_cast<double>(nearboids.size());

      for (Boid* bj : nearboids) {
        // Questa cosa non dovrebbe poter accadere poichè quelli uguali per ogni
        // nearboids vengono esclusi da isBoidVisibleInCone, non vede mai se
        // stesso
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
      separation_vel = -boid_params.separation * separation_vel;
      alignment_vel =
          boid_params.allignment * (invNear * alignment_vel - bi.Vel());
      cohesion_vel = boid_params.cohesion * (cm_pos - bi.Pos());

      cm_pos = invNear * cm_pos;
    }
    buffer_boid.update(separation_vel + alignment_vel + cohesion_vel, dt);

    buffer.emplace_back(buffer_boid);
  }
  return buffer;
}
}  // namespace bs