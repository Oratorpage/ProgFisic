#include "input.hpp"

#include <fstream>
#include <stdexcept>

namespace bs {
// Due scelte qua, o faccio un void trim(std::string& line) oppure lo lascio
// così, in teoria non ci dovrebbero essere problemi se anche non faccio una
// copia tanto leggo solo da file
std::string trimSpaces(std::string line) {
  std::size_t first{0};
  while (first < line.size() && line[first] == ' ') {
    ++first;
  }
  std::size_t last{line.size()};
  while (last > first && line[last - 1] == ' ') {
    --last;
  }

  return line.substr(first, last - first);
  // according to documentation if pos is equal to string length it returns an
  // empty string; if pos bigger than string legth then it throws out of range
}

int parseInt(std::string const& string_value) {
  std::size_t position{0};
  int value{std::stoi(string_value, &position)};
  if (position != string_value.size()) {
    throw std::runtime_error(
        "Invalid integer value (remove characters near numbers): " +
        string_value + " ; refer to the above instructions for typing.");
  }
  return value;
}

double parseDouble(std::string const& string_value) {
  std::size_t position{0};
  double value{std::stod(string_value, &position)};
  if (position != string_value.size()) {
    throw std::runtime_error(
        "Invalid double value (remove characters near numbers): " +
        string_value + " ; refer to the above instructions for typing.");
  }
  return value;
}

bool parseBool(std::string const& string_value) {
  if (string_value == "1" || string_value == "true") {
    return true;
  }
  if (string_value == "0" || string_value == "false") {
    return false;
  }
  throw std::runtime_error("Invalid boolean value: " + string_value +
                           " ; refer to the above instructions for typing.");
}

SimParams readSimulationParams(std::string const& path) {
  std::fstream filein(path);
  if (!filein) {
    throw std::runtime_error("File could not be opened: " + path);
  }
  SimParams parameters;
  std::string line;

  // This basically says that while i can get line from filein I'll put it into
  // line (look up reference better) when it cannot read a line anymore it stops
  while (std::getline(filein, line)) {
    line = trimSpaces(line);

    if (line.empty() || line[0] == '#') {
      continue;
    }

    std::size_t equal_position{line.find('=')};
    std::size_t colon_position{line.find(':')};

    if (equal_position == std::string::npos &&
        colon_position == std::string::npos) {
      throw std::runtime_error(
          "This line doesn't have an equal or colon delimiter: " + line);
    }

    std::string key;
    std::string value;

    if (equal_position == std::string::npos) {
      key = trimSpaces(line.substr(0, colon_position));
      value = trimSpaces(line.substr(colon_position + 1));
    } else if (colon_position == std::string::npos) {
      key = trimSpaces(line.substr(0, equal_position));
      value = trimSpaces(line.substr(equal_position + 1));
    }

    // C'è un modo migliore di fare questo che una catena di else if, anche solo
    // escludendo quelli già inseriti
    //  Simulation
    if (key == "non_pred_boidnum") {
      parameters.non_pred_boidnum = parseInt(value);
    } else if (key == "pred_boidnum") {
      parameters.pred_boidnum = parseInt(value);
    } else if (key == "separation") {
      parameters.separation = parseDouble(value);
    } else if (key == "allignment") {
      parameters.allignment = parseDouble(value);
    } else if (key == "cohesion") {
      parameters.cohesion = parseDouble(value);
    } else if (key == "detection_rad") {
      parameters.detection_rad = parseDouble(value);
    } else if (key == "danger_rad") {
      parameters.danger_rad = parseDouble(value);
    } else if (key == "angle_of_view") {
      parameters.angle_of_view = parseDouble(value);
    } else if (key == "toroidal") {
      parameters.toroidal = parseBool(value);
    } else if (key == "op_rad") {
      parameters.op_rad = parseBool(value);
    } else if (key == "dt") {
      parameters.dt == parseDouble(value);
    }
    // Render
    else if (key == "flockWindowTitle") {
      parameters.flockWindowTitle == value;
    } else if (key == "flockWindowWidth") {
      parameters.flockWindowWidth == parseInt(value);
    } else if (key == "flockWindowHeight") {
      parameters.flockWindowHeight == parseInt(value);
    } else if (key == "flockWindowPositionX") {
      parameters.flockWindowPositionX == parseInt(value);
    } else if (key == "flockWindowPositionY") {
      parameters.flockWindowPositionY == parseInt(value);
    } else if (key == "flockWindowFps") {
      parameters.flockWindowFps == parseInt(value);
    } else if (key == "statisticsWindowTitle") {
      parameters.statisticsWindowTitle == value;
    } else if (key == "statisticsWindowWidth") {
      parameters.statisticsWindowWidth == parseInt(value);
    } else if (key == "statisticsWindowHeight") {
      parameters.statisticsWindowHeight == parseInt(value);
    } else if (key == "statisticsWindowPositionX") {
      parameters.statisticsWindowPositionX == parseInt(value);
    } else if (key == "statisticsWindowPositionY") {
      parameters.statisticsWindowPositionY == parseInt(value);
    } else if (key == "statisticsWindowFps") {
      parameters.statisticsWindowFps == parseInt(value);
    }
    // Failsafe
    else {
      throw std::runtime_error("Unknown input key: " + key);
    }
  }

  // Voglio metterlo in una funzione il check?
  if (parameters.non_pred_boidnum < 0) {
    throw std::runtime_error("Negative non_pred_boinum value");
  }
  if (parameters.pred_boidnum < 0) {
    throw std::runtime_error("Negative pred_boinum value");
  }
  if (parameters.separation <= 0) {
    throw std::runtime_error("Negative or zero separation value");
  }
  if (parameters.allignment <= 0) {
    throw std::runtime_error("Negative or zero allignment value");
  }
  if (parameters.cohesion <= 0) {
    throw std::runtime_error("Negative or zero cohesion value");
  }
  if (parameters.detection_rad <= 0) {
    throw std::runtime_error("Negative or zero detection_rad value");
  }
  if (parameters.danger_rad <= 0) {
    throw std::runtime_error("Negative or zero danger_rad value");
  }
  if (parameters.angle_of_view < 0 || parameters.angle_of_view > 365.) {
    throw std::runtime_error("Negative or larger than 365 angle_of view value");
  }
  if (parameters.non_pred_boidnum == 0 && parameters.pred_boidnum == 0) {
    throw std::runtime_error(
        "non_pred_boidnum and pred_boidnum are both zero, no boids would be "
        "visualized");
  }
  if (parameters.dt <= 0) {
    throw std::runtime_error(
        "dt value cannot be negative, let time flow forward");
  }
  // The window conditions rely heavily on the sfml framework, thus the maximum
  // dimensions depend on one's hardware specifications
  if (parameters.flockWindowWidth <= 0) {
    throw std::runtime_error("Negative or zero width of the simulation window");
  }
  if (parameters.flockWindowHeight <= 0) {
    throw std::runtime_error(
        "Negative or zero height of the simulation window");
  }
  if (parameters.flockWindowPositionX <= 0) {
    throw std::runtime_error(
        "Negative or zero x position of the simulation window");
  }
  if (parameters.flockWindowPositionY <= 0) {
    throw std::runtime_error(
        "Negative or zero y position of the simulation window");
  }
  if (parameters.flockWindowFps <= 0) {
    throw std::runtime_error(
        "Negative or zero fps value for the statistics window");
  }
  if (parameters.statisticsWindowWidth <= 0) {
    throw std::runtime_error("Negative or zero width of the statistics window");
  }
  if (parameters.statisticsWindowHeight <= 0) {
    throw std::runtime_error(
        "Negative or zero height of the statistics window");
  }
  if (parameters.statisticsWindowPositionX <= 0) {
    throw std::runtime_error(
        "Negative or zero x position of the statistics window");
  }
  if (parameters.statisticsWindowPositionY <= 0) {
    throw std::runtime_error(
        "Negative or zero y position of the statistics window");
  }
  if (parameters.statisticsWindowFps <= 0) {
    throw std::runtime_error(
        "Negative or zero fps value for the statistics window");
  }

  return parameters;
}

}  // namespace bs