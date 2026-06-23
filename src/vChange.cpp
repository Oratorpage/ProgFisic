#include "vChange.hpp"

#include <cmath>

namespace flock {

// I discovered that I could have used std::hypot, would have needed to elevate
// it to pow 2 but maybe better?
// this whole part kinda sucks, I was terribly burnt out and I tried to push
// forward, let's redo it
double distSq(V2D const& a, V2D const& b) {
  double dx{a.x - b.x};
  double dy{a.y - b.y};
  return dx * dx + dy * dy;
}

// Devi fare il test per quando la velocità è zero nel caso
void angleBoidAdd(Boid& bi, Boid& bj, SimParams const& parameters, double gamma,
                  std::vector<Boid*>& nearboids) {
  double ang{normAngHorizon(bi, bj)};
  const double detection_rad_sq{parameters.detection_rad *
                                parameters.detection_rad};
  if (&bi != &bj &&
      ((gamma + parameters.angle_of_view / 2. - ang >= 0.) &&
       (gamma - parameters.angle_of_view / 2. - ang <= 0.)) &&
      distSq(bi.Pos(), bj.Pos()) < detection_rad_sq) {
    nearboids.push_back(&bj);
  }
}

// Qua aiuterebbe dividere la funzione di aggiornamento della velocità in due
// diverse basate sull'angolo o no, ridurrebbe il numero di check a loop che
// viene eseguito
// Però è bello che dal main chiamando velocity update ti cambi tutto da solo;
// alternativamente si possono fare un paio di funzioni ausiliarie: velocity
// update chiama in base all'angolo fullangleupdate o angleupdate

void velocityChangeBoids(std::vector<Boid>& Boids, double dt,
                         V2D const& flock_window_size_d,
                         SimParams const& params) {
  const double detection_rad_sq{params.detection_rad * params.detection_rad};
  const double danger_rad_sq{params.danger_rad * params.danger_rad};
  for (auto& bi : Boids) {
    std::vector<Boid*> nearboids;
    V2D separation_vel;
    V2D alignment_vel;
    V2D cm_pos;
    V2D cohesion_vel;
    double gamma{normGammaHorizon(bi)};
    // Here I need to invert the sign of the y coordinate of the velocity to get
    // the angle gamma because sfml uses a convention with the y axis growing
    // towards down, since bi is not an sfml object I cannot getRotation() and I
    // need to calculate it again but to avoid needless complexity I'll conform
    // to sfml convention
    // Do I need to do that though? Do I need inverted angles? I never interact
    // with sfml angles and besides, if I'll do It'll be easier to just make
    // those positive
    // Tomorrow we test for bugs

    // Based on the angle it creates a neighbouring boids vector* to calculate
    // vchange based on near boids that are visible
    if (params.angle_of_view == 360.) {
      for (auto& bj : Boids) {
        if (&bi != &bj && distSq(bi.Pos(), bj.Pos()) < detection_rad_sq) {
          nearboids.push_back(&bj);
        }
      }
    } else {
      for (auto& bj : Boids) {
        angleBoidAdd(bi, bj, params, gamma, nearboids);
      }
    }
    // Loop that calculates vchange based on nearby boids
    if (!nearboids.empty()) {
      double invNear = 1. / static_cast<double>(nearboids.size());
      for (auto& bj : nearboids) {
        if (&bi != bj) {
          // This is the update if bi is a predator and bj a prey
          // The predator does not wait for the prey to enter his danger_radius
          // and so the velocity gets updated whenever it sees it
          // Forse addirittura si potrebbe fare una funzione che gestisce il
          // cambio di velocità: una funzione che gestisce references e va a
          // modificare direttamente cm_pos e altro in base alla combinazione
          // predatore o non
          if (bi.IsPred() && !(bj->IsPred())) {
            separation_vel -= bj->Pos() - bi.Pos();

            cm_pos += bj->Pos();
          }
          // This is the update if bi is a prey and bj a predator
          // So does the prey, once it sees a predator it does not wait for it
          // to get to his danger_radius; moreover the separation is scaled by a
          // factor to make it more evasive
          if (!(bi.IsPred()) && bj->IsPred()) {
            separation_vel += (bj->Pos() - bi.Pos()) * 2.;

            alignment_vel -= bj->Vel();
            cm_pos -= bj->Pos();
          }
          // This is the update if bi is a predator and bj a predator
          if (bi.IsPred() && bj->IsPred()) {
            if (distSq(bi.Pos(), bj->Pos()) < danger_rad_sq) {
              separation_vel += bj->Pos() - bi.Pos();
            }
            alignment_vel += bj->Vel();
            cm_pos += bj->Pos();
          }
          // This is the update if bi is a prey and bj a predator
          if (!(bi.IsPred()) && !(bj->IsPred())) {
            if (distSq(bi.Pos(), bj->Pos()) < danger_rad_sq) {
              separation_vel += bj->Pos() - bi.Pos();
            }
            alignment_vel += bj->Vel();
            cm_pos += bj->Pos();
          }
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