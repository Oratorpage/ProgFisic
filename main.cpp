// It works, just not sfml 3.0, only sfml 2.6, possibly for the very change in
// std::optional and all the c++17 version stuff.
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
/*TODO: 1: FARE UN OROLOGIO E FAR Sì CHE IL TRIANGOLO CHE HO CREATO SI MUOVA IN
MANIERA CIRCOLARE UNIFORME 2: GENERARE UN CERTO NUMERO DI TRIANGOLI 3: FARE
MUOVERE QUESTI TRIANGOLI O A CASO O TUTTI IN UNA DIREZIONE IN MANIERA COSTANTE
4: PROVARE A CREARE UN SISTEMA DI RILEVAZIONE DI PROSSIMITà PER OGNI TRIANGOLO
5: FACENDOLI MUOVERE A CASO PROVARE A FAR Sì CHE NON SI SCONTRINO E IMPLEMENTARE
IL SISTEMA DI PROSSIMITà 6: ...SALTO... 7: IMPLEMENTARE LE TRE REGOLE DI MOTO 8:
OTTIMIZZAZIONE Generico: Guardare .reserve; decidere se dare valori iniziali
randomici o in base a set di dati/pattern/rng seed; decidere se cappare la
velocità massima e se definire un'accelerazione massima;
*/

// Struct che mi definisce i vettori bidimensionali e le loro operazioni
// inerenti
struct V2 {
  double x{0};
  double y{0};
};
V2 operator+(V2 const& a, V2 const& b) { return V2{a.x + b.x, a.y + b.y}; }
V2 operator-(V2 const& a, V2 const& b) { return V2{a.x - b.x, a.y - b.y}; }
V2 operator*(double g, V2 v) { return V2{v.x * g, v.y * g}; }
V2 operator*( V2 v, double g) { return V2{v.x * g, v.y * g}; }
V2 operator/(double g, V2 v) { return V2{v.x / g, v.y / g}; }
double operator*(V2 const& a, V2 const& b) {
  return double{a.x * b.x + a.y * b.y};
}
double operatorx(V2 const& a, V2 const& b) {
  return double{a.x * b.y - a.y * b.y};
}
double norm2(V2 const& a, V2 const& b) { return double{std::sqrt(a * b)}; }

class Boid {
 private:
  V2 velocity_{0, 0};
  V2 position_{400, 300};

 public:
  // Costructors & destructors (getters, setters?)
  Boid(V2 v, V2 p) : velocity_{v.x, v.y}, position_{p.x, p.y} {}
  Boid(V2 v) : velocity_{v.x,v.y}, position_{0.} {}
  //Boid(V2 p) : velocity_{0.}, position_{p.x,p.y} {}
  Boid() : velocity_{0.}, position_{0} {}
  V2 Vel() const { return velocity_; }
  V2 Pos() const { return position_; }

  // funzioni inerenti alla classe

  void update(double dt) {
    
  };
  void render() {};
};
// Should maybe implement the try catch architecture
int main() {
  sf::RenderWindow window(
      sf::VideoMode(800, 600), "SFML works!?",
      sf::Style::Default);  // Il primo int la lunghezza ed il secondo l'altezza
  window.setFramerateLimit(60);
  

  // Zona parametri regolabili
  const int N = 100;
  const double awarR = 25.0;
  // Mancano i valori s,a,c e se voglio mettere constraints su cose, quella è
  // implementazione, alla fine proprio

  // Creo il vettore boids dove ho tutti i miei singoli boid, li inizializzo
  // qua, poi ad ogni boid do una randomica velocità finale ed iniziale
  // std::vector<Boid> boids;
  // boids.reserve(N);  // Devo guardare la documentazione su .reserve
  // for (int i{0}; i < N; ++i) {
  //   Boid b(rvel, rpos);  // Dovranno essere dei V2
  //   boids.push_back(b);
  // }

  // Caratteristiche del boid
  sf::ConvexShape tri;
  tri.setPointCount(3);
  tri.setPoint(0, {20.f, 0.f});    // nose
  tri.setPoint(1, {-10.f, -8.f});  // back-left
  tri.setPoint(2, {-10.f, 8.f});   // back-right
  tri.setFillColor(sf::Color::Cyan);
  tri.setOutlineThickness(0.5f);
  tri.setOutlineColor(sf::Color::Black);
  tri.setPosition(400, 300);  // Questo poi lo dovrò togliere dopo

  // Questa è tutta una parte di event polling necessaria per il corretto
  // funzionamento della finestra; finchè la finestra è funzionante osservo cosa
  // gli accade ed in base a quello valuto
  sf::Clock clock;
  V2 p{1,1};//1 * std::acos(elapsed.asSeconds()), 1 * std::asin(elapsed.asSeconds())
  V2 v{10,10};//-10 * std::asin(elapsed.asMilliseconds()), 10 * std::acos(elapsed.asMilliseconds())
  Boid b(v, p);
  
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::KeyPressed:
          if (event.key.code == sf::Keyboard::Escape) {
            window.close();
          }
          break;
      }
    }
    

    double dt = clock.restart().asSeconds();
    b.Pos() = b.Pos() + (b.Vel() * dt);
    tri.setPosition(b.Pos().x, b.Pos().y);
    // if (b.Pos().x < 0) b.Pos().x = b.Pos().x + 800;
    // if (b.Pos().x >= 800) b.Pos().x -= 800;
    // if (b.Pos().y < 0) b.Pos().y += 600;
    // if (b.Pos().y >= 600) b.Pos().y -= 600;
    // La sequenza di queste tre linee è fondamentale, la prima ripulisce i
    // frame vecchi, la seconda rendera il desiderio, la terza effettivamente fa
    // comparire il desiderio; sempre disegnare dopo aver pulito
    window.clear(sf::Color(150, 150, 150));
    window.draw(tri);
    window.display();
  }

  return 0;
}