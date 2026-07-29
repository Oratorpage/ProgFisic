#ifndef BS_RENDERPARAMS_HPP
#define BS_RENDERPARAMS_HPP

#include <string>

namespace bs {
struct RenParams {
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
}  // namespace bs

#endif