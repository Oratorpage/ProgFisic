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
V2& operator+=(V2& v, V2 const& r) {
  v.x += r.x;
  v.y += r.y;
  return v;
}
// V2& operator*=(V2& v, double d) {
//   v.x *= d;
//   v.y *= d;
// }

double operator*(V2 const& a, V2 const& b) {
  return double{a.x * b.x + a.y * b.y};
}
double norm2(V2 const& a, V2 const& b) { return double{std::sqrt(a * b)}; }
// Probably not gonna use these but maybe useful, remove before handing in
//  V2 operator/(double const& g, V2 const& v) { return V2{v.x / g, v.y / g}; }

//  double operatorx(V2 const& a, V2 const& b) {
//    return double{a.x * b.y - a.y * b.y};
//  }

// Specialized variable defining a singular element of the flock
class Boid {
 private:
  V2 velocity_{0, 0};
  V2 position_{0, 0};

 public:
  // Costructors
  Boid(V2 v, V2 p) : velocity_{v.x, v.y}, position_{p.x, p.y} {}
  Boid(V2 v) : velocity_{v.x, v.y} {}
  // Boid(V2 p) : position_{p.x,p.y} {} Fa overload strano, non va bene, non sa
  // se posizione o velocità, trova un trick per farlo funzionare
  V2 Vel() const { return velocity_; }
  V2 Pos() const { return position_; }

  // funzioni inerenti alla classe
  // Inizializzazione del singolo boid con i valori immessi dall'utente

  //update basato sul parametro di cambio velocità e sul tipo di spazio deciso
  void update(double const& dt, V2 const& tsize, V2& vup,
              bool const& toroidal) {
    velocity_ += vup * dt;
    position_ += velocity_ * dt;
    if (toroidal == true) {
      velocity_ += vup * dt;
      position_ += velocity_ * dt;
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
      // Velocity constraint for the toroidal space, avoids particle
      // accellerator behaviour
      if (velocity_.x > 100) {
        velocity_.x = 100;
      }
      if (velocity_.x < -100) {
        velocity_.x = -100;
      }
      if (velocity_.y > 100) {
        velocity_.y = 100;
      }
      if (velocity_.y < -100) {
        velocity_.y = -100;
      }
    }
    if (position_.x < 20) {
      velocity_.x += 10.;
    };
    if (position_.y < 20) {
      velocity_.y += 10.;
    };
    if (position_.x > tsize.x - 20) {
      velocity_.x -= 10.;
    };
    if (position_.y > tsize.y - 20) {
      velocity_.y -= 10.;
    };
  }

  // Uso il metodo solamente per cambiare il valore, il calcolo di vup me lo
  // faccio con una funzione prima che non cambia i valori della classe
  void vchange(V2 const& vup) { velocity_ += vup; }
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

  // Should create a struct for the values or a function to imput all of these
  // values, it's a bit ugly and inefficient like this, if I'd like to change
  // the values I'd have no way to do it
  std::cout << "Input the values for the desired simulation: N:";
  int N;
  if (!(std::cin >> N) || N <= 0) {
    std::cout
        << "Negative, zero or not integer number of boids, terminating... ";
    return 1;
  }
  std::cout << "s: ";
  double s;
  if (!(std::cin >> s) || s <= 0) {
    std::cout << "Negative, zero or not integer value for the separation "
                 "coefficient, terminating... ";
    return 1;
  }
  std::cout << "a: ";
  double a;
  if (!(std::cin >> a) || a <= 0) {
    std::cout << "Negative, zero or not integer value for the alignment "
                 "coefficient, terminating... ";
    return 1;
  }
  std::cout << "c: ";
  double c;
  if (!(std::cin >> c) || c <= 0) {
    std::cout << "Negative, zero or not integer value for the cohesion "
                 "coefficient, terminating... ";
    return 1;
  }
  // ds è la distanza di influenza della regola per i vicini, per i boid  la cui
  // distanza è minore di ds allora compio il calcolo per vsep
  std::cout << "dangerrad: ";
  double dangerrad;
  if (!(std::cin >> dangerrad) || dangerrad <= 0) {
    std::cout
        << "Negative, zero or not integer value for the influence distance "
           "coefficient, terminating... ";
    return 1;
  }
  std::cout << "Toroidal space active (1 for yes, 0 for no): ";
  bool toroidal;
  if (!(std::cin >> toroidal)) {
    std::cout << "Not a valid value, terminating... ";
    return 1;
  }
  // std::cout << "Operational Radiuses active (1 for yes, 0 for no): ";
  // bool visrad;
  // if (!(std::cin >> visrad)) {
  //   std::cout << "Not a valid value, terminating... ";
  //   return 1;
  // }

  std::vector<Boid> boids;
  boids.reserve(N);  // Devo guardare la documentazione su .reserve
  // Qua non è un loop sugli elementi di boids perchè ovviamente è vuoto, ho
  // solo aumentato la capacità del vettore per non dover reallocare
  for (int i{0}; i < N; ++i) {
    boids.emplace_back(rvel(), rpos(tsize));
  }

  // Caratteristiche grafiche del boid
  sf::ConvexShape tri;
  tri.setPointCount(3);
  tri.setPoint(0, {20.f, 0.f});    // nose
  tri.setPoint(1, {-10.f, -8.f});  // back-left
  tri.setPoint(2, {-10.f, 8.f});   // back-right
  tri.setFillColor(sf::Color::Cyan);
  tri.setOutlineThickness(0.5f);
  tri.setOutlineColor(sf::Color::Black);
  tri.setPosition(0, 0);

  sf::Clock clock;
  const double PI{3.14159265358979323846264338327950288};
  const double detectrad{45.};
  // Con 40 non è male

  // if (visrad == true) {
  //   sf::CircleShape circdetr;
  //   circdetr.setRadius(static_cast<float>(detectrad));
  //   circdetr.setOrigin(static_cast<float>(detectrad),
  //                      static_cast<float>(detectrad));
  //   circdetr.setOutlineColor(sf::Color::Green);
  //   circdetr.setFillColor(sf::Color::Transparent);
  //   circdetr.setOutlineThickness(5);
  //   //  //Raggio di pericolo
  //   sf::CircleShape circdanr;
  //   circdanr.setRadius(static_cast<float>(dangerrad));
  //   circdanr.setOrigin(static_cast<float>(dangerrad),
  //                      static_cast<float>(dangerrad));
  //   circdanr.setOutlineColor(sf::Color::Red);
  //   circdanr.setFillColor(sf::Color::Transparent);
  //   circdanr.setOutlineThickness(5);
  // }

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

    // Questo invece lo potrei racchiudere all'interno di una funzione move
    for (auto& bi : boids) {
      std::vector<Boid*> nearboids;
      V2 vsep;
      V2 vallig;
      V2 xcm;
      V2 vcoes;
      // aggiunta per ogni iterazione su boids del Boid bj al vettore dei
      // puntatori dei Boid vicini a bi
      for (auto& bj : boids) {
        if (&bi != &bj) {
          double distsq =
              (bi.Pos().x - bj.Pos().x) * (bi.Pos().x - bj.Pos().x) +
              (bi.Pos().y - bj.Pos().y) * (bi.Pos().y - bj.Pos().y);
          if (distsq < detectrad * detectrad) {
            nearboids.push_back(&bj);
          }
        }
      }
      // calcolo delle componenti della velocità dalle regole, solo se ha dei
      // vicini
      if (!nearboids.empty()) {
        double invNear = 1. / nearboids.size();
        for (auto& bj : nearboids) {
          if (&bi != bj) {
            double distsq =
                (bi.Pos().x - (*bj).Pos().x) * (bi.Pos().x - (*bj).Pos().x) +
                (bi.Pos().y - (*bj).Pos().y) * (bi.Pos().y - (*bj).Pos().y);
            if (distsq < dangerrad * dangerrad) {
              vsep += (*bj).Pos() - bi.Pos();
            }
            vallig += (*bj).Vel();
            xcm += (*bj).Pos();
          }
        }
        vsep = -s * vsep;
        vallig = a * (invNear * vallig - bi.Vel());
        xcm = invNear * xcm;
        vcoes = c * (xcm - bi.Pos());
      }
      V2 vup = vsep + vallig + vcoes;
      bi.update(dt, tsize, vup, toroidal);
    }

    // Questo lo potrei racchiudere all'interno di una funzione render
    window.clear(sf::Color(150, 150, 150));
    for (auto const& b : boids) {
      V2 p = b.Pos();
      V2 v = b.Vel();
      double ang = std::atan2(v.y, v.x) * 180.0 / PI;
      tri.setRotation(static_cast<float>(ang));
      tri.setPosition(static_cast<float>(p.x), static_cast<float>(p.y));

      // circdetr.setPosition(static_cast<float>(p.x), static_cast<float>(p.y));
      // circdanr.setPosition(static_cast<float>(p.x), static_cast<float>(p.y));

      window.draw(tri);

      // window.draw(circdetr);

      // window.draw(circdanr);
    }
    window.display();
  }

  return 0;
}