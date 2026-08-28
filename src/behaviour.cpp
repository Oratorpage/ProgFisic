#include "behaviour.hpp"

#include <cmath>
#include <iostream>

namespace bs {

double distSq(V2D const& a, V2D const& b) {
  V2D d = a - b;
  return dotprod(d, d);
}

constexpr double distLim{1.e-2};
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
  // At this point it is necessarly within the detection radius
  if (boid_params.angle_of_view >= 360.) {
    return true;
  }

  // The vector of the velocity of the boid a, the one that gets compared
  // against all others, is the vector representing the axis passing through a,
  // based on that and the vector of the distance with the other boid, b, the
  // angle can be found
  const V2D vect_velA{a.Vel()};
  const V2D vect_distanceAB{b.Pos() - a.Pos()};

  const double velA_norm{norm(vect_velA)};
  const double distance_norm{norm(vect_distanceAB)};

  if (distance_norm <= distLim) {
    return true;
  }
  // This is intentional: if the speed is zero, it will be able to see all
  // around himself with an angle of view = 360
  if (velA_norm <= valLim) {
    return true;
  }
  const double cos_half_angle_view{
      std::cos(boid_params.angle_of_view * 0.5 * piconst / 180.)};

  // Here the cosine relation with the norm is utilized, it results in the
  // cosine of the angle between the velocity of A and the distanceAB
  const double cos_angle{dotprod(vect_velA, vect_distanceAB) /
                         (velA_norm * distance_norm)};

  return cos_angle >= cos_half_angle_view - valLim;
}

std::vector<Boid const*> collectVisibleBoids(
    std::vector<Boid> const& flock, Boid const& bi,
    BoidProperties const& boid_params) {
  std::vector<Boid const*> nearboids;
  nearboids.reserve(flock.size() - 1);

  for (Boid const& bj : flock) {
    if (isBoidVisibleInCone(bi, bj, boid_params)) {
      nearboids.emplace_back(&bj);
    }
  }
  return nearboids;
}

// Here one could change input parameters and directly use the Simulation
std::vector<Boid> applyFlockBehaviouralMovement(
    std::vector<Boid> const& flock, double const dt,
    BoidProperties const& boid_params) {
  std::vector<Boid> buffer;
  buffer.reserve(flock.size());

  const double danger_rad_sq{boid_params.danger_radius *
                             boid_params.danger_radius};

  for (Boid const& bi : flock) {
    std::vector<Boid const*> nearboids_i{
        collectVisibleBoids(flock, bi, boid_params)};

    Boid buffer_boid{bi};
    V2D separation_vel;
    V2D alignment_vel;
    V2D cohesion_vel;

    V2D cm_pos;

    // Loop that calculates vchange based on nearby boids
    if (!nearboids_i.empty()) {
      const double inv_near = 1. / static_cast<double>(nearboids_i.size());

      for (Boid const* bj : nearboids_i) {
        const V2D bj_pos{bj->Pos()};
        const V2D bi_pos{bi.Pos()};
        const double b_dist_sq{distSq(bj_pos, bi_pos)};

        // predator and prey
        if (bi.IsPredator() && !(bj->IsPredator())) {
          separation_vel -= bj_pos - bi_pos;
          cm_pos += bj_pos;
        }

        // prey and predator
        if (!(bi.IsPredator()) && bj->IsPredator()) {
          separation_vel += (bj_pos - bi_pos) * 2.;
          alignment_vel -= bj->Vel();
          cm_pos -= bj_pos;
        }

        // 2 predators
        if (bi.IsPredator() && bj->IsPredator()) {
          if (b_dist_sq < danger_rad_sq) {
            separation_vel += bj_pos - bi_pos;
          }
          alignment_vel += bj->Vel();
          cm_pos += bj_pos;
        }

        // 2 preys
        if (!(bi.IsPredator()) && !(bj->IsPredator())) {
          if (b_dist_sq < danger_rad_sq) {
            separation_vel += bj_pos - bi_pos;
            if (norm(bj_pos - bi_pos) < 1.) {
              separation_vel += (100.) * (bj_pos - bi_pos);
            }
          }
          alignment_vel += bj->Vel();
          cm_pos += bj_pos;
        }
      }
      cm_pos *= inv_near;

      separation_vel = -boid_params.separation * separation_vel;
      alignment_vel =
          boid_params.alignment * (inv_near * alignment_vel - bi.Vel());
      cohesion_vel = boid_params.cohesion * (cm_pos - bi.Pos());
    }

    buffer_boid.completeUpdate(separation_vel + alignment_vel + cohesion_vel,
                               dt, boid_params.max_speed,
                               boid_params.min_speed);

    buffer.emplace_back(buffer_boid);
  }
  return buffer;
}

}  // namespace bs