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
  // If it is already within radius then it can just be checked if it is within
  // the cone
  if (boid_params.angle_of_view >= 360.) {
    return true;
  }

  // The vector of the velocity of the boid a, the one that gets compared
  // against all others, is the vector representing the axis passing through a,
  // based on that and the vector of the distance with the other boid, b, the
  // angle can be found
  const V2D vect_velA{a.Vel()};
  const V2D vect_distanceAB{a.Pos() - b.Pos()};

  const double velA_norm{norm(vect_velA)};
  const double distance_norm{norm(vect_distanceAB)};

  if (distance_norm <= valLim) {
    return true;
  }
  const double cos_half_angle_view{
      std::cos(boid_params.angle_of_view * 0.5 * piconst / 180.)};

  // Here the cosine relation with the norm is utilized
  const double cos_angle{dotprod(vect_velA, vect_distanceAB) / velA_norm *
                         distance_norm};

  if (cos_angle >= cos_half_angle_view && velA_norm <= valLim) {
    return true;
  }
  return cos_angle >= cos_half_angle_view;
}

std::vector<Boid*> collectVisibleBoids(std::vector<Boid>& flock, Boid const& bi,
                                       BoidProperties const& boid_params) {
  std::vector<Boid*> nearboids;

  nearboids.reserve(flock.size() - 1);
  for (Boid& bj : flock) {
    if (isBoidVisibleInCone(bi, bj, boid_params)) {
      nearboids.emplace_back(&bj);
    }
  }
  return nearboids;
}

// Qua gli si potrebbe direttamente fare l'input della simulazione
std::vector<Boid> applyFlockBehaviouralMovement(
    std::vector<Boid>& flock, double dt, BoidProperties const& boid_params) {
  std::vector<Boid> buffer{flock};

  const double danger_rad_sq{boid_params.danger_radius *
                             boid_params.danger_radius};

  for (Boid const& bi : flock) {
    std::vector<Boid*> nearboids{collectVisibleBoids(flock, bi, boid_params)};

    Boid buffer_boid{bi};
    V2D separation_vel;
    V2D alignment_vel;
    V2D cohesion_vel;

    V2D cm_pos;

    // Loop that calculates vchange based on nearby boids
    if (!nearboids.empty()) {
      const double invNear = 1. / static_cast<double>(nearboids.size());

      for (Boid* bj : nearboids) {
        // predator and prey
        if (bi.IsPredator() && !(bj->IsPredator())) {
          separation_vel -= bj->Pos() - bi.Pos();
          cm_pos += bj->Pos();
        }

        // prey and predator
        if (!(bi.IsPredator()) && bj->IsPredator()) {
          separation_vel += (bj->Pos() - bi.Pos()) * 2.;
          alignment_vel -= bj->Vel();
          cm_pos -= bj->Pos();
        }

        // 2 predators
        if (bi.IsPredator() && bj->IsPredator()) {
          if (distSq(bi.Pos(), bj->Pos()) < danger_rad_sq) {
            separation_vel += bj->Pos() - bi.Pos();
          }
          alignment_vel += bj->Vel();
          cm_pos += bj->Pos();
        }

        // 2 preys
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
          boid_params.alignment * (invNear * alignment_vel - bi.Vel());
      cohesion_vel = boid_params.cohesion * (cm_pos - bi.Pos());

      cm_pos = invNear * cm_pos;
    }

    // Devo fare il check e la limitazione sulla velocità prima di ogni
    // piazzarlo sul buffer
    buffer_boid.update(separation_vel + alignment_vel + cohesion_vel, dt);
    buffer_boid.limitVelocity(boid_params.max_speed);

    buffer.emplace_back(buffer_boid);
  }
  return buffer;
}
}  // namespace bs