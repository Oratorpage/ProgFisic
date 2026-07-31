#ifndef BS_STATISTICS_HPP
#define BS_STATISTICS_HPP

#include "string"
#include "v2D.hpp"

namespace bs {
struct Statistics {
  V2D cm_pos{0, 0};
  V2D avg_vel{0, 0};
  int in_window_count{0};
  std::string statistics_output{"Invalid"};
  
  //  Qua volendo si potrebbe mettere lo step della simulazione, utile o non
  //  ancora non lo so,intanto lo scrivo
};
}  // namespace bs

#endif