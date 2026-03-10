// It works, just not sfml 3.0, only sfml 2.6, possibly for the very change in
// std::optional and all the c++17 version stuff.
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
// g++ -std=c++17 boids.cpp -lsfml-graphics -lsfml-window -lsfml-system

// A quanto pare dovrò mettere tutto quanto all'interno del namespace quindi sì
// conviene direttamente riscrivere tutto da capo

// Bidimensional vectors and operations
struct V2 {
  double x{0};
  double y{0};
};
V2 operator+(V2 const& a, V2 const& b) { return V2{a.x + b.x, a.y + b.y}; }
V2 operator-(V2 const& a, V2 const& b) { return V2{a.x - b.x, a.y - b.y}; }
V2 operator*(double const& g, V2 const& v) { return V2{v.x * g, v.y * g}; }
V2 operator*(V2 const& v, double const& g) { return V2{v.x * g, v.y * g}; }
// Probably not gonna use these but maybe useful, remove before handing in
//  V2 operator/(double const& g, V2 const& v) { return V2{v.x / g, v.y / g}; }
//  double operator*(V2 const& a, V2 const& b) {
//    return double{a.x * b.x + a.y * b.y};
//  }
//  double operatorx(V2 const& a, V2 const& b) {
//    return double{a.x * b.y - a.y * b.y};
//  }
//  double norm2(V2 const& a, V2 const& b) { return double{std::sqrt(a * b)}; }

// Specialized variable defining a singular element of the flock
class Boid {
 private:
  V2 velocity_{0, 0};
  V2 position_{0, 0};

 public:
  // Costructors
  Boid(V2 v, V2 p) : velocity_{v.x, v.y}, position_{p.x, p.y} {}
  Boid(V2 v) : velocity_{v.x, v.y} {}
  // Boid(V2 p) : position_{p.x,p.y} {} Da risolvere prima di consegnare
  V2 Vel() const { return velocity_; }
  V2 Pos() const { return position_; }

  // funzioni inerenti alla classe
  // Inizializzazione del singolo boid con i valori immessi dall'utente

  // Updating is necessary to change it through time
  // Maybe I should implement in the update function che window toroidal
  // constraints
  void update(double const& dt, V2 const& tsize) {
    position_ = position_ + velocity_ * dt;
    if (position_.x < 0) {
      position_.x = tsize.x;
    };
    if (position_.y < 0) {
      position_.y = tsize.y;
    };
    if (position_.x > tsize.x) {
      position_.x = 0.;
    };
    if (position_.y > tsize.y) {
      position_.y = 0.;
    };
  }
  // Should render boid on the screen
  // void render() {}
};

// Generare una posizione iniziale randomica aiuta nell'ottenere risultati
// diversi
V2 rvel() {
  std::random_device r;
  std::mt19937 gen(r());
  std::uniform_real_distribution<> distrx(-25, 25);
  std::uniform_real_distribution<> distry(-25, 25);
  return V2{distrx(gen), distry(gen)};
}
V2 rpos(V2 const& tsize) {
  std::random_device r;
  std::mt19937 gen(r());
  std::uniform_real_distribution<> distrx(0, tsize.x);
  std::uniform_real_distribution<> distry(0, tsize.y);
  return V2{distrx(gen), distry(gen)};
}

// Should maybe implement the try catch architecture
int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Flock Test",
                          sf::Style::Default);
  window.setPosition(sf::Vector2i(750, 200));
  sf::Vector2u size = window.getSize();
  // Non ci dovrebbe essere problema con questo static cast in quanto passo da
  // un unsigned int ad un double, porterà a problemi forse con schermi/finestre
  // molto, molto grandi
  V2 tsize{static_cast<double>(size.x), static_cast<double>(size.y)};

  // Mancano i valori s,a,c e se voglio mettere constraints su cose, quella è
  // implementazione, alla fine proprio, andrà fatto con vettore, magari
  // aggiungo una classe flock che prenda come variabile i boid ed i parametri

  std::cout << "Input the values for the desired simulation: N:";
  int N;
  if (!(std::cin >> N) || N <= 0) {
    std::cout
        << "Negative, zero or not integer number of boids, terminating... ";
    return 1;
  }
  // std::cout << "s: \n";
  // double s;
  // std::cin >> s;
  // std::cout << "a: \n";
  // double a;
  // std::cin >> a;
  // std::cout << "c: \n";
  // double c;
  // std::cin >> c;
  // std::cout << " d: \n";
  // double d;
  // std::cin >> d;
  // std::cout << "ds; \n";
  // double ds;
  // std::cin >> ds;

  std::vector<Boid> boids;
  boids.reserve(N);  // Devo guardare la documentazione su .reserve
  // Qua non è un loop sugli elementi di boids perchè ovviamente è vuoto, ho
  // solo aumentato la capacità del vettore per non dover reallocare
  for (int i{0}; i < N; ++i) {
    boids.emplace_back(rvel(), rpos(tsize));
  }

  // Caratteristiche del boid
  sf::ConvexShape tri;
  tri.setPointCount(3);
  tri.setPoint(0, {20.f, 0.f});    // nose
  tri.setPoint(1, {-10.f, -8.f});  // back-left
  tri.setPoint(2, {-10.f, 8.f});   // back-right
  tri.setFillColor(sf::Color::Cyan);
  tri.setOutlineThickness(0.5f);
  tri.setOutlineColor(sf::Color::Black);
  tri.setPosition(400, 300);

  sf::Clock clock;
  const double PI = 3.14159265358979323846264338327950288;

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
    // Qua devo essere pronto a spiegare perchè non è con gli indici: è meglio,
    // no errori indici, per ogni elemento b di boids mi esegue la variazione
    // della posizione
    // Questo loop direi che lo posso racchiudere direttamente nella funzione
    // update
    for (auto& b : boids) {
      b.update(dt, tsize);
    }

    window.clear(sf::Color(150, 150, 150));
    // Bisogna risolvere il problema che quando i boid vengono portati
    // dall'altro lato, la loro velocità nella direzione del teletrasporto si
    // annulla, il che mi stranisce perchè la velocità per ora non è variabile
    // in base alla differenza di posizione ma dovrebbe essere costante
    // Come questo loop lo potrei racchiudere nella funzione render
    for (auto const& b : boids) {
      V2 p = b.Pos();
      V2 v = b.Vel();
      tri.setPosition(static_cast<float>(p.x), static_cast<float>(p.y));
      double ang = std::atan2(v.y, v.x) * 180.0 / PI;
      tri.setRotation(static_cast<float>(ang));
      window.draw(tri);
    }
    window.display();
  }

  return 0;
}