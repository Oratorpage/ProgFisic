#ifndef BS_WINDOWPARAMS_HPP
#define BS_WINDOWPAAMS_HPP

#include <string>

namespace bs {
struct WindowParams {
  std::string title{"Window"};

  unsigned int width{800U};
  unsigned int height{600U};

  int posX{100};
  int posY{100};

  unsigned int fps{60U};
};

}  // namespace bs

#endif