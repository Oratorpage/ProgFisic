#include "simulation.hpp"

// In simulazione devo racchiudere tutto e solamente quello che è necessario
// all'algoritmo per i boids e lo stormo

namespace bs {
// Dovrei includere direttamente BoidProperties nel costruttore di Simulation?
// Anche una prima inizializzazione di stats? Suppongo dipende da quando viene
// chiamato l'oggetto, nel programma mi devo assicurare che quando venga
// chiamato non ritorni cose a caso. Non è necessario no che per una good cpp
// practice ogni oggetto appartenente ad una classe venga completamente
// inizializzato?
Simulation::Simulation(SimParams const& sp, WorldParams const& wp)
    : world_{wp},
      dt_{sp.dt},
      total_boids_{sp.pred_boidnum + sp.non_pred_boidnum} {
  buildFlock(sp);
}

void Simulation::buildFlock(SimParams const& sp) {
  flock_.reserve(static_cast<long unsigned int>(total_boids_));

  for (int i{0}; i < sp.non_pred_boidnum; ++i) {
    flock_.emplace_back(randVel(), randPos(world_.Dimensions()));
  }
  for (int i{0}; i < sp.pred_boidnum; ++i) {
    flock_.emplace_back(randVel(), randPos(world_.Dimensions()), true);
  };
}

World const& Simulation::currentWorld() const { return world_; }
BoidProperties const& Simulation::boidProperties() const { return properties_; }
std::vector<Boid> const& Simulation::currentFlock() const {
  return flock_;
}  // Il ritorno di questo vettore sarà un casino vero?
double const Simulation::deltaTime() const { return dt_; }
Statistics const& Simulation::currentStatistics() const { return stats_; }

void Simulation::calculateStats(std::vector<Boid> const& flock) {
  stats_.cm_pos = {0, 0};
  stats_.avg_vel = {0, 0};
  stats_.in_window_count = {0};
  for (Boid b : flock) {
    V2D p = b.Pos();
    V2D v = b.Vel();

    // Questo va cambiato in base a view perchè così perde di significato; è
    // ovvio che i boid nel mondo non varieranno di numero ma il numero di
    // quelli visibili dipende dalla visuale che ha la camera
    if (b.Pos().x < (world_.Width()) && b.Pos().y < (world_.Height()) &&
        b.Pos().x > 0 && b.Pos().y > 0) {
      ++stats_.in_window_count;
    }
    stats_.cm_pos += p;
    stats_.avg_vel += v;
  }
  stats_.cm_pos = stats_.cm_pos / static_cast<double>(flock.size());
  stats_.avg_vel = stats_.avg_vel / static_cast<double>(flock.size());

  std::string cm_string{
      "Position of the cm_pos: x :" + std::to_string(stats_.cm_pos.x) +
      " , y: " + std::to_string(stats_.cm_pos.y) + "\n"};
  std::string avg_vel_string{"Average velocity of the total flock: x :" +
                             std::to_string(stats_.avg_vel.x) + " , y: " +
                             std::to_string(stats_.avg_vel.y) + "\n"};
  std::string in_view_string{"Boids present in window view: " +
                             std::to_string(stats_.in_window_count) + "\n"};
}

void tick() {
  // Fill this up bro, it must be a loop calling the resulting velocity function
  // from the behavioural rules we set and some other stuff
  std::vector<Boid> flock_buffer{};
}

}  // namespace bs