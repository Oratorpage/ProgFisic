// It works, just not sfml 3.0, only sfml 2.6, possibly for the very change in
// std::optional and all the c++17 version stuff.
#include <SFML/Graphics.hpp>
#include <cmath>

// Struct che mi definisce i vettori bidimensionali e le loro operazioni
// inerenti
struct V2 {
  double x{0};
  double y{0};
};
V2 operator+(V2 const& a, V2 const& b) { return V2{a.x + b.x, a.y + b.y}; }
V2 operator-(V2 const& a, V2 const& b) { return V2{a.x - b.x, a.y - b.y}; }
V2 operator*(double g, V2 v) { return V2{v.x * g, v.y * g}; }
V2 operator/(double g, V2 v) { return V2{v.x / g, v.y / g}; }
double operator*(V2 const& a, V2 const& b) {
  return double{a.x * b.x + a.y * b.y};
}
double operatorx(V2 const& a, V2 const& b) {
  return double{a.x * b.y - a.y * b.y};
}
double norm2(V2 const& a, V2 const& b) {
  return double{std::sqrt(a*b)};
}

class Boid {
 private:
  V2 velocity_{0, 0};
  V2 position_{400, 300};
  double awaR_{25};
  double const dlim_{5};

 public:
  // Costructors & destructors (getters, setters?)
  Boid(V2 v, V2 p) : velocity_{v.x,v.y}, position_{p.x, p.y} {}
  V2 Vel() {return velocity_;}
  V2 Pos() {return position_;}

  // funzioni inerenti alla classe
  

  void update() {};
  void render() {};
};
// Should maybe implement the try catch architecture
int main() {
  sf::RenderWindow window(
      sf::VideoMode(800, 600), "SFML works!?",
      sf::Style::Default);  // Il primo int la lunghezza ed il secondo l'altezza
  sf::CircleShape shape(100.f);  // Il parametro float di questo regola il
                                 // raggio della circonferenza
  shape.setFillColor(sf::Color::Blue);

  sf::ConvexShape tri;
  tri.setPointCount(3);
  tri.setPoint(0, {20.f, 0.f});    // nose
  tri.setPoint(1, {-10.f, -8.f});  // back-left
  tri.setPoint(2, {-10.f, 8.f});   // back-right
  tri.setFillColor(sf::Color::Cyan);
  tri.setOutlineThickness(0.5f);
  tri.setOutlineColor(sf::Color::Black);
  tri.setPosition(400, 300);
  // Questa è tutta una parte di event polling necessaria per il corretto
  // funzionamento della finestra; finchè la finestra è funzionante osservo cosa
  // gli accade ed in base a quello valuto
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
    // La sequenza di queste tre linee è fondamentale, la prima ripulisce i
    // frame vecchi, la seconda rendera il desiderio, la terza effettivamente fa
    // comparire il desiderio; sempre disegnare dopo aver pulito
    window.clear(sf::Color(150, 150, 150));
    window.draw(tri);
    window.display();
  }

  return 0;
}