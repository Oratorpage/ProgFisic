// Defines the parameters that will be used
#ifndef BS_SIMULATIONPARAMS_HPP
#define BS_SIMULATIONPARAMS_HPP

namespace bs {

struct SimParams {
  // Simulation
  int non_pred_boidnum{10};  // Come caso standard cosa scelg0, 0 o 10?
  int pred_boidnum{0};
  double separation{0.};
  double allignment{0.};
  double cohesion{0.};
  double detection_rad{0.};
  double danger_rad{0.};
  double angle_of_view{0.};
  bool toroidal{false};
  bool op_rad{false};
  double dt{0.001};

  // Render
  std::string flockWindowTitle{"Simulation"};
  unsigned int flockWindowWidth{800};
  unsigned int flockWindowHeight{600};
  unsigned int flockWindowPositionX{750};
  unsigned int flockWindowPositionY{200};
  unsigned int flockWindowFps{60};

  std::string statisticsWindowTitle{"Statistics"};
  unsigned int statisticsWindowWidth{600};
  unsigned int statisticsWindowHeight{400};
  unsigned int statisticsWindowPositionX{0};
  unsigned int statisticsWindowPositionY{200};
  unsigned int statisticsWindowFps{60};
};

/*
 // op_rad creates two circular shapes that represent the detection_radius (the
 radius wherein boids are seen by others) and the danger_radius (the radius
 whithin which there is a danger of collision with others)


                                 detect
                               ç-------ç
                            #             #
                         #                   #
                       /         danger        \
                      /         .-----.         \
                     |         /       \         |
                     |        |    Δ    |        |
                     |         \       /         |
                      \         '""""""         /
                       \                       /
                         #                   #
                           #               #
                             "--_______--"


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