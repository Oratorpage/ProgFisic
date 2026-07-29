#include "simulation.hpp"

namespace bs {

void Simulation::buildFlock(SimParams const& sp) {
  flock_.reserve(static_cast<long unsigned int>(total_boids_));

  for (int i{0}; i < sp.non_pred_boidnum; ++i) {
    flock_.emplace_back(randVel(),
                        randPos({static_cast<double>(sp.flockWindowWidth),
                                 static_cast<double>(sp.flockWindowHeight)}));
  }
  for (int i{0}; i < sp.pred_boidnum; ++i) {
    flock_.emplace_back(randVel(),
                        randPos({static_cast<double>(sp.flockWindowWidth),
                                 static_cast<double>(sp.flockWindowHeight)}),
                        true);
  };
}

// Zio banana, questa espansione e contrazione di conoscenza e tecniche scoperte
// è sconvolgente; arrivo ora alla separazione tra mondo simulato e visuale
// attiva per la simulazione

void Simulation::calculateStats(std::vector<Boid> const& flock) {
  stats_.cm_pos = {0, 0};
  stats_.avg_vel = {0, 0};
  stats_.in_window_count = {0};
  for (Boid b : flock) {
    V2D p = b.Pos();
    V2D v = b.Vel();

    if (b.Pos().x < static_cast<double>(flockWindow_.getSize().x) &&
        b.Pos().y < static_cast<double>(flockWindow_.getSize().y) &&
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

  std::string fps_string{
      "flockwindow fps: " + std::to_string(flockWindowFps_) + "\n" +
      "statisticswindow fps:" + std::to_string(statisticsWindowFps_) + "\n"};

  stats_.output.setString(cm_string + avg_vel_string + in_view_string +
                          fps_string);
}

Simulation::Simulation(SimParams const& sp)
    : dt_{sp.dt}, total_boids_{sp.pred_boidnum + sp.non_pred_boidnum} {
  buildFlock(sp);
}

int const Simulation::currentStep() const { return current_step_; }
double const Simulation::deltaTime() const { return dt_; }
std::vector<Boid> const Simulation::currentFlock() const {
  return flock_;
}  // Il ritorno di questo vettore sarà un casino vero?

}  // namespace bs