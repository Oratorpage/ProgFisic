#include "vChange.hpp"

#include <cmath>

namespace flock {

// I discovered that I could have used std::hypot, would have needed to elevate
// it to pow 2 but maybe better?
double distSq(V2D const& a, V2D const& b) {
  double dx{a.x - b.x};
  double dy{a.y - b.y};
  return dx * dx + dy * dy;
}
// Adesso funziona correttamente
double normGammaHorizon(Boid const& bi) {
  double gamma{0.};
  constexpr double PI{3.14159265358979323846264338327950288};
  // First quadrant and second
  if ((bi.Vel().x > 0. && bi.Vel().y < 0.) ||
      (bi.Vel().x < 0. && bi.Vel().y < 0.)) {
    gamma = -std::atan2(bi.Vel().y, bi.Vel().x) * 180. / PI;
  }
  // Third quadrant and fourth
  else if ((bi.Vel().x < 0. && bi.Vel().y > 0.) ||
           (bi.Vel().x > 0. && bi.Vel().y > 0.)) {
    gamma = 360. - std::atan2(bi.Vel().y, bi.Vel().x) * 180. / PI;
  }  // Special case
  else if (bi.Vel().x > 0. && bi.Vel().y == 0.) {
    gamma = 0.;
  } else if (bi.Vel().x == 0. && bi.Vel().y < 0.) {
    gamma = 90.;
  } else if (bi.Vel().x < 0. && bi.Vel().y == 0.) {
    gamma = 180.;
  } else if (bi.Vel().x == 0. && bi.Vel().y > 0.) {
    gamma = 270.;
  } else if (bi.Vel().x == 0. && bi.Vel().y == 0.) {
    gamma = 0.;
  } else {
    throw std::runtime_error(
        "The velocity of the boid was not a compatible value to deduce an "
        "angle with the horizon (counter-clockwise)");
  }
  return gamma;
}
// Questo adesso funziona correttamente
double normAngHorizon(Boid const& bi, Boid const& bj) {
  double ang{0.};
  V2D dist{bj.Pos() - bi.Pos()};
  constexpr double PI{3.14159265358979323846264338327950288};
  // First and second quadrant
  if ((dist.x > 0. && dist.y < 0.) || (dist.x < 0. && dist.y < 0.)) {
    ang = -std::atan2(dist.y, dist.x) * 180. / PI;
  }  // Second and third quadrant
  else if ((dist.x < 0. && dist.y > 0.) || (dist.x > 0. && dist.y > 0.)) {
    ang = 360. - std::atan2(dist.y, dist.x) * 180. / PI;
  } else if (dist.x > 0. && dist.y == 0.) {
    ang = 0.;
  } else if (dist.x == 0. && dist.y < 0.) {
    ang = 90.;
  } else if (dist.x < 0. && dist.y == 0.) {
    ang = 180.;
  } else if (dist.x == 0. && dist.y > 0.) {
    ang = 270.;
  } else if (dist.x == 0. && dist.y == 0.) {
    ang = 0.;  // Dipende poi dalla condizione che impongo per l'aggiunta nel
               // vettore
  } else {
    throw std::runtime_error(
        "The position of the boids was not a compatible value to deduce an "
        "angle with the horizon (counter-clockwise)");
  }
  return ang;
}

// Devi fare il test per quando la velocità è zero nel caso
void angleBoidAdd(Boid& bi, Boid& bj, SimParams const& parameters, double gamma,
                  std::vector<Boid*>& nearboids) {
  double ang{normAngHorizon(bi, bj)};
  if ((ang - (gamma + parameters.angle_of_view / 2.)) <= 0 ||
      (ang - (gamma - parameters.angle_of_view / 2.)) >= 0) {
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
    V2D allignament_vel;
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
      allignament_vel =
          params.allignment * (invNear * allignament_vel - bi.Vel());
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