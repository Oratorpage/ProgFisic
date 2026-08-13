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

  while (ren_.isFWOpen()) {
    // Dubito sia la gestione degli eventi a causare problemi, essendo una
    // funzione entra nel while di gestione degli eventi solo se prende un
    // evento, finchè non lo gestisce rimane nel while ma poichè di default
    // breaka allora esce comunque
    ren_.manageEvents();
    // sim_.uniteViewStats(ren_.getViewStats(sim_.currentFlock()));

    // Il problema è probabilmente qua (non è la limitazione della velocità
    // perchè l'avevo fatto) Bruh, ho semplificato l'algoritmo in modo da capire
    // se il problema sia l'update o altro ma comunque non funzia
    sim_.tick();
    // There is no way to have the render's framerate be fixed and indipendent
    // from the simulation time; either I calculate all of the simulation's
    // steps and save them in a log file, which allows me to flip between them
    // like a video at the speed I desire, or the framerate of the render will
    // always be as fast as the simulation.

    // Sposto il render sotto il calcolo perchè più semplice da manneggiare per
    // le mie necessità, così va sistemato l'edge case della prima
    // inizializzazione del testo
    //Bruh andiamo per esclusione a questo punto
    ren_.renderFrame(sim_);
  }
}
//È possibile che l'errore derivi da un'incapsulazione della finestra in una classe ed il non riuscire ad accedere ad altro? Non trovo alcun problema con il render o la simulazione, se anche 

}  // namespace bs