#include "conductor.hpp"

// In conductor devo racchiudere tutto e solamente quello che è necessario al
// far cooperare ed unire render e simulazione in maniera da farli lavorare in
// modo coeso e sensato

namespace bs {

Conductor::Conductor(Config const& configuration, double time_factor)
    : con_{configuration},
      sim_{configuration.wp, configuration.bp, configuration.sp},
      ren_{configuration.rp, configuration.bp},
      time_factor_{time_factor} {
  conInvariant();
}

void Conductor::conInvariant() {
  if (time_factor_ <= 0) {
    throw std::invalid_argument{
        "time_factor value is not acceptable, cannot be less or equal to "
        "zero"};
  }
}

void Conductor::start() {
  sf::Clock clock;
  double time_buffer{};

  while (ren_.isFWOpen()) {
    ren_.manageEvents();
    // sim_.uniteViewStats(ren_.getViewStats(sim_.currentFlock()));
    ren_.renderFrame(sim_);

    double elapsed = clock.restart().asSeconds();
    time_buffer += elapsed * time_factor_;
    // Ok il problema è qua: io non ho sim_.deltaTime() come il tempo impiegato
    // dalla simulazione per fare un tick ma come il dt con cui lavora, dunque
    // questo non ha senso, va cambiato
    // Prendo come time_buffer il tempo che ci ha messo a fare il render e con
    // questa configurazione al secondo ciclo anche il loop del tempo(feedback
    // positivo) e finchè è maggiore del dt della simulazione (0.01) faccio
    // andare la simulazione e ci tolgo di nuovo il valore costante 0.01
    // Non si può fare così, va cambiato deltaTime e secondo me con questo
    // ordine di render e simulazione anche l'algoritmo per il tempo costante
    while (time_buffer >= sim_.deltaTime()) {
      sim_.tick();
      time_buffer -= sim_.deltaTime();
    }
  }
}

}  // namespace bs