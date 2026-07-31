#include "simulation.hpp"

#include "behaviour.hpp"

// In simulazione devo racchiudere tutto e solamente quello che è necessario
// all'algoritmo per i boids e lo stormo

namespace bs {
// Dovrei includere direttamente BoidProperties nel costruttore di Simulation?
// Anche una prima inizializzazione di stats? Suppongo dipende da quando viene
// chiamato l'oggetto, nel programma mi devo assicurare che quando venga
// chiamato non ritorni cose a caso. Non è necessario no che per una good cpp
// practice ogni oggetto appartenente ad una classe venga completamente
// inizializzato?
Simulation::Simulation(WorldParams const& wp, BoidProperties const& bp,
                       SimParams const& sp)
    : world_{wp},
      boid_properties_{bp},

      total_boids_{sp.pred_boidnum + sp.non_pred_boidnum},
      dt_{sp.dt} {
  buildFlock(sp);
}
// Statistiche ha senso inizializzarlo a zero/invalido direttamente nella struct
// in maniera tale che se uno crea un oggetto simulation ma non vuole usarle è
// comunque un oggetto valido e pienamente inizializzato; chiaramente
// all'inizio, finchè non ci si opera sopra saranno spazzatura quindi ha senso
// tipo string{"invalid"}; forse il calcolo delle statistiche andrebbe fatto
// nell'update della simulazione e poi passato al render, sempre seguendo la
// regola, se tolgo il render, la simulazione sopravvive da sola?; Inoltre mi
// giunge la domanda, se le uniche funzioni che ho per simulation sono o il
// calcolo delle statistiche o il tick della simulazione dove inevitambilmente
// calcolo le statistiche, allora posso lasciarlo non inizializzato? Non potrei
// fare altro e se so che inizialimente è inutilizzabile allora basta non usarlo

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
BoidProperties const& Simulation::boidProperties() const {
  return boid_properties_;
}
std::vector<Boid> const& Simulation::currentFlock() const {
  return flock_;
}  // Il ritorno di questo vettore sarà un casino vero?
double const Simulation::deltaTime() const {
  return dt_;
}  // È corretto che sia const il risultato no? per ora non ho bisogno che venga
   // modificato
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
  stats_.statistics_output = cm_string + avg_vel_string + in_view_string;
}

// La posizione in cui dovrei mettere il calcolo delle statistiche in conductor
// dipende dal mio approccio, se voglio avere il render anche della
// configurazione iniziale (step_0) allora devo mettere il render prima rispetto
// alla simulazione, altrimenti, se non mi interessa il render dello step zero
// in quanto è l'evoluzione che mi interessa posso lasciarlo così; la cosa
// fondamentale è che se faccio prima il render che il primo step della
// simulazione allora tutto ciò che io ho settato come default della simulazione
// funzioni effettivamente correttamente e restituisca una cosa sensata,
// altrimenti non serve
void Simulation::tick() {
  flock_ = applyFlockBehaviouralMovement(flock_, dt_, boid_properties_);
}

}  // namespace bs