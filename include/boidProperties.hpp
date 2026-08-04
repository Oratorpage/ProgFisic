#ifndef BS_BOIDPROPERTIES_HPP
#define BS_BOIDPROPERTIES_HPP

namespace bs {
struct BoidProperties {
  double detection_radius{};
  double danger_radius{};

  // Total angle of vision of the Boid
  double angle_of_view{};

  double max_speed{};

  double separation{0.};
  double alignment{0.};
  double cohesion{0.};
};

// The angle_of_view in combination with the danger_radius and detection_radius
// create a sort of FOV, this could be elaborated more to achieve a more
// structural result in future development; tweaking the FOV values and the
// varius coefficents, the behaviour of any kind of group of creatures can be
// replicated and simulated up to a certain accuracy, from a school of fish to a
// herd of cows to group of humans

/*
 // angle_of_view changes the way boids see each other making it possible only
 through a certain angle, based on the type of creature the angle should vary,
 it is up to manual insertion


                \                   |                   /
                 \                  |   .^^^^^^.       /
                  \                 | ,'        ',    / detection distance
                   \                |'            '  /
                    \               |              '/
                     \              |              /
                      \             |             /
                       \            |            /
                        \           |           /
                         \          |          /
                          \         |,' ' ',  / danger distance
                           \        |       '/
                            \       |       /
                             \      |      /
                              \     |  α  /
                               \    |.''./
                                \   |   /
                                 \  |  /
                                  \ | /
                                   \|/
                                    Δ
                                   /|\
                                  / | \
                                 /  |  \
                                /   |   \
                               /    |    \
                              /     |     \
                             /      |      \
                            /       |       \
                           /        |        \

The danger distance is based on danger_rad when angle_of_view != 0. or !=365.,
Controlla se l'angolo di input è la metà o è già l'angolo completo, questo
deriva dalla funzione che gestisce l'angolo per l'inserzione dei boid
*/

}  // namespace bs

#endif