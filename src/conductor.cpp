#include "conductor.hpp"

namespace bs {

Conductor::Conductor(SimParams const& sp, double time_factor)
    : sim_{sp}, time_factor_{time_factor} {}

void Conductor::start(SimParams const& sp) {
  sf::Clock clock;
  double time_buffer{};

  while (ren_.isFWOpen()) {
    ren_.manageEvents();

    double elapsed = clock.restart().asSeconds();
    time_buffer += elapsed * time_factor_;
    while(time_buffer >= sim_.deltaTime()){
        sim_.update();
        time_buffer -= sim_.deltaTime();
    }

    ren_.renderFrame(sim_.currentFlock(),)
    
    // Sistema il clock in modo che il dt sia costante 0.00833 0.01667
    // Questo adesso provo a normalizzarlo a costante tramite un elapsed come
    // game loop documentazione sfml poi se funzia bene e lo lascio così, se
    // no dt fluttuante
    // Avere il dt costante sistemerebbe anche il problema di interazione
    // quando c'è tanto da calcolare, come nel caso di oprad true
    velocityChangeBoids(boids, dt, flock_window_size_d, parameters);

    renderFrame(FlockWindow, IoWindow, boids, parameters, flock_window_size_d,
                non_pred_boid, pred_boid, detection_circle, danger_circle,
                cm_circle, statistics, dt);
  }
};

}  // namespace bs