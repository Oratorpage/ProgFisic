#include "simulation.hpp"

#include <iostream>

#include "behaviour.hpp"

// In simulazione devo racchiudere tutto e solamente quello che è necessario
// all'algoritmo per i boids e lo stormo

namespace bs {
Simulation::Simulation(WorldParams const& wp, BoidProperties const& bp,
                       SimParams const& sp)
    : world_{wp},
      boid_properties_{bp},

      total_boids_{sp.pred_boidnum + sp.non_pred_boidnum},
      dt_{sp.dt} {
  simInvariant();
  buildFlock(sp, bp);
  firstStats(flock_);
}

void Simulation::buildFlock(SimParams const& sp, BoidProperties const& bp) {
  flock_.reserve(static_cast<long unsigned int>(total_boids_));

  for (int i{0}; i != sp.non_pred_boidnum; ++i) {
    flock_.emplace_back(randVel(bp.max_speed), randPos(world_.getDimensions()),
                        false);
  }
  for (int i{0}; i != sp.pred_boidnum; ++i) {
    flock_.emplace_back(randVel(bp.max_speed), randPos(world_.getDimensions()),
                        true);
  };
}

void Simulation::firstStats(std::vector<Boid> const& flock) {
  stats_.cm_pos = {0, 0};
  stats_.avg_vel = {0, 0};
  // stats_.in_window_count = {0};
  for (Boid b : flock) {
    V2D p = b.Pos();
    V2D v = b.Vel();

    // Here another division in responsability is needed between the render and
    // the simulation, it only depends on how many are in view
    if (b.Pos().x < (world_.getWidth()) && b.Pos().y < (world_.getHeight()) &&
        b.Pos().x > 0 && b.Pos().y > 0) {
      // ++stats_.in_window_count;
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

  stats_.statistics_output = cm_string + avg_vel_string;
}

// The boid parameters coefficients can for now be smaller than zero, does it
// make sense? I'm not sure yet
void Simulation::simInvariant() {
  if (boid_properties_.detection_radius <= 0.) {
    throw std::invalid_argument{
        "detection_radius value is not acceptable, cannot be less or equal to "
        "zero \n"};
  }
  if (boid_properties_.danger_radius <= 0.) {
    throw std::invalid_argument{
        "danger_radius value is not acceptable, cannot be less or equal to "
        "zero \n"};
  }
  if (boid_properties_.angle_of_view <= 0.) {
    throw std::invalid_argument{
        "angle_of_view value is not acceptable, cannot be less or equal to "
        "zero \n"};
  }
  if (boid_properties_.angle_of_view > 360.) {
    throw std::invalid_argument{
        "angle_of_view value is not acceptable, cannot be larger than 360 \n"};
  }
  if (boid_properties_.max_speed <= 0.) {
    throw std::invalid_argument{
        "Initialize the max_speed with a positive and non-zero value, the "
        "negative case is taken care of \n"};
  }
  if (boid_properties_.min_speed <= 0. ||
      boid_properties_.min_speed >= boid_properties_.max_speed) {
    throw std::invalid_argument{
        "Initialize the min_speed with a positive and non-zero value, also "
        "cannot be larger or equal than the max_speed\n"};
  }
  if (boid_properties_.danger_radius > boid_properties_.detection_radius) {
    throw std::invalid_argument{
        "danger_radius value is larger than detection_radius value, it is not "
        "acceptable \n"};
  }
  if (total_boids_ <= 0) {
    throw std::invalid_argument{
        "total_boids value is not acceptable, cannot be less or equal to "
        "zero \n"};
  }
  if (dt_ <= 0.) {
    throw std::invalid_argument{
        "dt value is not acceptable, cannot be less or equal to zero \n"};
  }
}

World const& Simulation::currentWorld() const {
  return world_;
}  // This has never been used as many other things, they are footsteps for a
   // future improvement
BoidProperties const& Simulation::boidProperties() const {
  return boid_properties_;
}
std::vector<Boid> const& Simulation::currentFlock() const { return flock_; }
double Simulation::getSimdt() const { return dt_; }
Statistics const& Simulation::currentStatistics() const { return stats_; }

void Simulation::calculateStats(std::vector<Boid> const& flock) {
  stats_.cm_pos = {0, 0};
  stats_.avg_vel = {0, 0};
  for (Boid b : flock) {
    V2D p = b.Pos();
    V2D v = b.Vel();

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

  stats_.statistics_output = cm_string + avg_vel_string;
}

void Simulation::tick() {
  if (world_.isToroidal()) {
    world_.wrap(flock_);
  } else {
    world_.contain(flock_, boid_properties_);
  }

  flock_ = applyFlockBehaviouralMovement(flock_, dt_, boid_properties_);

  calculateStats(flock_);
}

}  // namespace bs