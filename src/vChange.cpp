#include "vChange.hpp"
// forse devi includere anche vector, anche se è già incluso nell'hpp dunque non
// so

namespace flock {

double distSq(V2D const& a, V2D const& b) {
  double dx{a.x - b.x};
  double dy{a.y - b.y};
  return dx * dx + dy * dy;
}

void velocityChangeBoids(std::vector<Boid>& Boids, double dt,
                         V2D const& flock_window_size_d,
                         SimParams const& params) {
  const double detection_rad_sq{params.detection_rad * params.detection_rad};
  const double danger_rad_sq{params.danger_rad * params.danger_rad};
  for (auto& bi : Boids) {
    std::vector<Boid*> nearboids;
    V2D separation_vel;
    V2D allignament_vel;
    V2D cm_pos;
    V2D cohesion_vel;
    // Creating a neighbouring boids vector* to calculate vchange based on near
    // boids
    for (auto& bj : Boids) {
      if (&bi != &bj && distSq(bi.Pos(), bj.Pos()) < detection_rad_sq) {
        nearboids.push_back(&bj);
      }
    }
    // Loop that calculates vchange based on nearby boids
    if (!nearboids.empty()) {
      double invNear = 1. / static_cast<double>(nearboids.size());
      for (auto& bj : nearboids) {
        if (&bi != bj) {
          // This is the update if bi is a predator and bj a prey
          if (bi.IsPred() && !(bj->IsPred())) {
            separation_vel -= bj->Pos() - bi.Pos();

            cm_pos += bj->Pos();
          }
          // This is the update if bi is a prey and bj a predator
          if (!(bi.IsPred()) && bj->IsPred()) {
            separation_vel += (bj->Pos() - bi.Pos()) * 2.;

            allignament_vel -= bj->Vel();
            cm_pos -= bj->Pos();
          }
          // This is the update if bi is a predator and bj a predator
          if (bi.IsPred() && bj->IsPred()) {
            if (distSq(bi.Pos(), bj->Pos()) < danger_rad_sq) {
              separation_vel += bj->Pos() - bi.Pos();
            }
            allignament_vel += bj->Vel();
            cm_pos += bj->Pos();
          }
          // This is the update if bi is a prey and bj a predator
          if (!(bi.IsPred()) && !(bj->IsPred())) {
            if (distSq(bi.Pos(), bj->Pos()) < danger_rad_sq) {
              separation_vel += bj->Pos() - bi.Pos();
            }
            allignament_vel += bj->Vel();
            cm_pos += bj->Pos();
          }
        }
      }
      separation_vel = -params.separation * separation_vel;
      allignament_vel = params.allignment * (invNear * allignament_vel - bi.Vel());
      cm_pos = invNear * cm_pos;
      cohesion_vel = params.cohesion * (cm_pos - bi.Pos());
    }
    // If there are no near boids it will update anyway but vup will be 0
    // because of the standard inizialization of the V2D
    V2D vup{separation_vel + allignament_vel + cohesion_vel};
    bi.update(dt, flock_window_size_d, vup, params.toroidal);
  }
}
}  // namespace flock