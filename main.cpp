// It works, just not sfml 3.0, only sfml 2.6, possibly for the very change in
// std::optional and all the c++17 version stuff.
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>
// g++ -std=c++17 boids.cpp -lsfml-graphics -lsfml-window -lsfml-system

// A quanto pare dovrò mettere tutto quanto all'interno del namespace quindi sì
// conviene direttamente riscrivere tutto da capo

// Bidimensional vector of double components and pertinent operations
struct V2D {
  double x{0};
  double y{0};

  V2D& operator+=(V2D const& r) {
    x += r.x;
    y += r.y;
    return *this;
  }

  V2D& operator-=(V2D const& r) {
    x -= r.x;
    y -= r.y;
    return *this;
  }

  V2D& operator*=(double m) {
    x *= m;
    y *= m;
    return *this;
  }

  V2D& operator/=(double d) {
    x /= d;
    y /= d;
    return *this;
  }
};
inline V2D operator+(V2D lhs, V2D const& rhs) { return lhs += rhs; }

inline V2D operator-(V2D lhs, V2D const& rhs) { return lhs -= rhs; }

inline V2D operator*(double m, V2D lhs) { return lhs *= m; }
inline V2D operator*(V2D lhs, double m) { return lhs *= m; }

inline V2D operator/(V2D lhs, double d) { return lhs /= d; }

inline double dotprod(V2D const& a, V2D const& b) {
  return a.x * b.x + a.y * b.y;
}
inline double xprod(V2D const& a, V2D const& b) {
  return a.x * b.y - a.y * b.x;
}

// Specialized variable defining a singular element of the flock
class Boid {
 private:
  V2D velocity_{0., 0.};
  V2D position_{0., 0.};
  static constexpr double maxspeedtor{150};
  static constexpr double maxspeed{300};

 public:
  // Costructors
  Boid(V2D v, V2D p) : velocity_{v}, position_{p} {}
  // Il costruttore per singola v o p non è per ora necessario, se lo diventerà
  // andrà deciso come implementarlo
  V2D Vel() const { return velocity_; }
  V2D Pos() const { return position_; }

  // update basato sul parametro di cambio velocità e sul tipo di spazio deciso
  // Questo update basato su dt così però crea un feedback loop, più tempo passa
  // a causa dei calcoli e più sarà l'aggiornamento, più sarà la velocità;
  // pessima cosa per un rendering stabile e scientifico, -> cambialo
  void update(double dt, V2D const& tsize, V2D const& vup, bool const& toroidal) {
    velocity_ += vup * dt;
    position_ += velocity_ * dt;
    // Qua posso anche non mettere  == true a quanto pare per cui lo lascerei
    // così
    if (toroidal) {
      if (position_.x < 0) {
        position_.x = tsize.x;
      }
      if (position_.y < 0) {
        position_.y = tsize.y;
      }
      if (position_.x > tsize.x) {
        position_.x = 0.;
      }
      if (position_.y > tsize.y) {
        position_.y = 0.;
      }
      // Velocity constraint for the toroidal space, avoids particle
      // accellerator behaviour
      if (velocity_.x > maxspeedtor) {
        velocity_.x = maxspeedtor;
      }
      if (velocity_.x < -maxspeedtor) {
        velocity_.x = -maxspeedtor;
      }
      if (velocity_.y > maxspeedtor) {
        velocity_.y = maxspeedtor;
      }
      if (velocity_.y < -maxspeedtor) {
        velocity_.y = -maxspeedtor;
      }
    } else {
      // A non-toroidal space shouldn't need a velocity limiter, it is built in
      if (position_.x < 20) {
        velocity_.x += 10.;
      }
      if (position_.y < 20) {
        velocity_.y += 10.;
      }
      if (position_.x > tsize.x - 20) {
        velocity_.x -= 10.;
      }
      if (position_.y > tsize.y - 20) {
        velocity_.y -= 10.;
      }
      // unfortunately for extreme parameters it needs an additional constraint
      if (velocity_.x > maxspeed) {
        velocity_.x = maxspeed;
      }
      if (velocity_.x < -maxspeed) {
        velocity_.x = -maxspeed;
      }
      if (velocity_.y > maxspeed) {
        velocity_.y = maxspeed;
      }
      if (velocity_.y < -maxspeed) {
        velocity_.y = -maxspeed;
      }
    }
  }
};

// Generare una posizione iniziale randomica aiuta nell'ottenere risultati
// diversi
V2D rvel() {
  std::random_device r;
  std::mt19937 gen(r());
  std::uniform_real_distribution<> distrx(-25, 25);
  std::uniform_real_distribution<> distry(-25, 25);
  return V2D{distrx(gen), distry(gen)};
}
V2D rpos(V2D const& tsize) {
  std::random_device r;
  std::mt19937 gen(r());
  std::uniform_real_distribution<> distrx(0, tsize.x);
  std::uniform_real_distribution<> distry(0, tsize.y);
  return V2D{distrx(gen), distry(gen)};
}

// Should maybe implement the try catch architecture
int main() {
  sf::RenderWindow flockwindow(sf::VideoMode(800, 600), "Flock View",
                               sf::Style::Default);
  flockwindow.setPosition(sf::Vector2i(750, 200));
  sf::Vector2u fwsize = flockwindow.getSize();
  // Non ci dovrebbe essere problema con questo static cast in quanto passo da
  // un unsigned int ad un double, porterà a problemi forse con schermi/finestre
  // molto, molto grandi, vedi se problemi già noti
  V2D fwstsize{static_cast<double>(fwsize.x), static_cast<double>(fwsize.y)};

  sf::RenderWindow iowindow(sf::VideoMode(600, 400), "I/O View",
                            sf::Style::Default);
  sf::Vector2u iosize = iowindow.getSize();
  V2D iostsize{static_cast<double>(iosize.x), static_cast<double>(iosize.y)};
  // Should create a struct for the values or a function to imput all of these
  // values, it's a bit ugly and inefficient like this, if I'd like to change
  // the values I'd have no way to do it
  // Almeno incapsularle in una funzione ensomma
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
  std::cout << "Operational Radiuses active (1 for yes, 0 for no): ";
  bool oprad;
  if (!(std::cin >> oprad)) {
    std::cout << "Not a valid value, terminating... ";
    return 1;
  }

  std::vector<Boid> boids;
  boids.reserve(N);  // Devo guardare la documentazione su .reserve
  // Qua non è un loop sugli elementi di boids perchè ovviamente è vuoto, ho
  // solo aumentato la capacità del vettore per non dover reallocare
  for (int i{0}; i < N; ++i) {
    boids.emplace_back(rvel(), rpos(fwstsize));
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

  // Questo devo capire se posso incapsularlo in un qualche modo perchè
  // altrimenti definire tutta sta roba ogni volta è inutile
  //  if (oprad == true) {
  sf::CircleShape circdetr;
  circdetr.setRadius(static_cast<float>(detectrad));
  circdetr.setOrigin(static_cast<float>(detectrad),
                     static_cast<float>(detectrad));
  circdetr.setOutlineColor(sf::Color::Green);
  circdetr.setFillColor(sf::Color::Transparent);
  circdetr.setOutlineThickness(5);
  // Raggio di pericolo
  sf::CircleShape circdanr;
  circdanr.setRadius(static_cast<float>(dangerrad));
  circdanr.setOrigin(static_cast<float>(dangerrad),
                     static_cast<float>(dangerrad));
  circdanr.setOutlineColor(sf::Color::Red);
  circdanr.setFillColor(sf::Color::Transparent);
  circdanr.setOutlineThickness(5);
  // }

  sf::CircleShape cmpos;
  cmpos.setRadius(5);
  cmpos.setOutlineColor(sf::Color::Black);
  cmpos.setFillColor(sf::Color::Black);

  sf::Font tnrfont;
  if (tnrfont.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
    std::cout << "Font file was  loaded correctly \n";
  }
  sf::Text text;
  text.setFont(tnrfont);
  text.setCharacterSize(15);
  // Loop inerente alle finestre e ciò che succede per ogni frame
  while (flockwindow.isOpen()) {
    sf::Event event;
    while (flockwindow.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          flockwindow.close();
          break;

        case sf::Event::KeyPressed:
          if (event.key.code == sf::Keyboard::Escape) {
            flockwindow.close();
          }
          break;
      }
    }
    // chiamare close su finestra già chiusa
    while (iowindow.isOpen() && iowindow.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          iowindow.close();
          break;

        case sf::Event::KeyPressed:
          if (event.key.code == sf::Keyboard::Escape) {
            iowindow.close();
          }
          break;
      }
    }
    // Sistema il clock in modo che il dt sia costante
    double dt = clock.restart().asSeconds();

    // Questo invece lo potrei racchiudere all'interno di una funzione move
    for (auto& bi : boids) {
      std::vector<Boid*> nearboids;
      V2D vsep;
      V2D vallig;
      V2D xcm;
      V2D vcoes;
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
                (bi.Pos().x - bj->Pos().x) * (bi.Pos().x - bj->Pos().x) +
                (bi.Pos().y - bj->Pos().y) * (bi.Pos().y - bj->Pos().y);
            if (distsq < dangerrad * dangerrad) {
              vsep += bj->Pos() - bi.Pos();
            }
            vallig += bj->Vel();
            xcm += bj->Pos();
          }
        }
        vsep = -s * vsep;
        vallig = a * (invNear * vallig - bi.Vel());
        xcm = invNear * xcm;
        vcoes = c * (xcm - bi.Pos());
      }
      V2D vup = vsep + vallig + vcoes;
      bi.update(dt, fwstsize, vup, toroidal);
    }

    // Questo lo potrei racchiudere all'interno di una funzione render
    flockwindow.clear(sf::Color(150, 150, 150));
    V2D cm;
    V2D avgv;
    int inwcount{0};
    for (auto const& b : boids) {
      V2D p = b.Pos();
      V2D v = b.Vel();
      double ang = std::atan2(v.y, v.x) * 180.0 / PI;
      tri.setRotation(static_cast<float>(ang));
      tri.setPosition(static_cast<float>(p.x), static_cast<float>(p.y));
      // Possible bug/weird behaviour for non toroidal space but oprad on
      if (oprad == true) {
        circdetr.setPosition(static_cast<float>(p.x), static_cast<float>(p.y));
        circdanr.setPosition(static_cast<float>(p.x), static_cast<float>(p.y));
        flockwindow.draw(circdetr);
        flockwindow.draw(circdanr);
      }

      if (b.Pos().x < fwstsize.x && b.Pos().y < fwstsize.y && b.Pos().x > 0 &&
          b.Pos().y > 0) {
        inwcount += 1;
      }
      flockwindow.draw(tri);

      cm += p;
      avgv += v;
    }
    cm = cm / N;
    avgv = avgv / N;

    std::string strxcm = "Position of the cm: x :" + std::to_string(cm.x) +
                         " , y: " + std::to_string(cm.y) + "\n";
    std::string stravgv =
        "Velocity of the total flock: x :" + std::to_string(avgv.x) +
        " , y: " + std::to_string(avgv.y) + "\n";
    std::string strinwc =
        "Boids present in window view: " + std::to_string(inwcount) + "\n";
    text.setString(strxcm + stravgv + strinwc);

    cmpos.setPosition(static_cast<float>(cm.x), static_cast<float>(cm.y));
    flockwindow.draw(cmpos);

    iowindow.clear(sf::Color(150, 150, 150));
    iowindow.draw(text);

    iowindow.display();
    flockwindow.display();
    inwcount = 0;
  }
  // Controlla se è il distruttore che elimina iowindow oppure se è la logica
  // del programma
}