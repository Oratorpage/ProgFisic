#include "input.hpp"

#include <fstream>
#include <stdexcept>
#include <unordered_set>

namespace bs {

enum class Section { none, simulation, render, world, boids };

void readSimulationSection(SimParams& sim_par,
                           std::unordered_set<std::string>& initialized_keys,
                           std::string const& key,
                           std::string const& string_value,
                           std::size_t line_number) {
  if (!initialized_keys.insert(key).second) {
    throw std::runtime_error{"Duplicate simulation parameter key" + key +
                             "at line" + std::to_string(line_number) + "\n"};
  } else if (key == "non_pred_boidnum") {
    sim_par.non_pred_boidnum = parseInt(string_value);
  } else if (key == "pred_boidnum") {
    sim_par.pred_boidnum = parseInt(string_value);
  } else if (key == "dt") {
    sim_par.dt = parseDouble(string_value);
  } else {
    throw std::runtime_error{"Unknown simulation parameter: " + key +
                             " at line: " + std::to_string(line_number) + "\n"};
  }
}

void readRenderSection(RenParams& ren_par,
                       std::unordered_set<std::string>& initialized_keys,
                       std::string const& key, std::string const& string_value,
                       std::size_t line_number) {
  if (!initialized_keys.insert(key).second) {
    throw std::runtime_error{"Duplicate render parameter key" + key +
                             "at line" + std::to_string(line_number) + "\n"};
  } else if (key == "flock_window_title") {
    ren_par.flock_window_parameters.title = string_value;
  } else if (key == "flock_window_width") {
    ren_par.flock_window_parameters.width = parseUnsignedInt(string_value);
  } else if (key == "flock_window_height") {
    ren_par.flock_window_parameters.height = parseUnsignedInt(string_value);
  } else if (key == "flock_window_posX") {
    ren_par.flock_window_parameters.posX = parseUnsignedInt(string_value);
  } else if (key == "flock_window_posY") {
    ren_par.flock_window_parameters.posY = parseUnsignedInt(string_value);
  } else if (key == "flock_window_fps") {
    ren_par.flock_window_parameters.fps = parseUnsignedInt(string_value);
  }

  else if (key == "statistics_window_title") {
    ren_par.statistics_window_parameters.title = string_value;
  } else if (key == "statistics_window_width") {
    ren_par.statistics_window_parameters.width = parseUnsignedInt(string_value);
  } else if (key == "statistics_window_height") {
    ren_par.statistics_window_parameters.height =
        parseUnsignedInt(string_value);
  } else if (key == "statistics_window_posX") {
    ren_par.statistics_window_parameters.posX = parseUnsignedInt(string_value);
  } else if (key == "statistics_window_posY") {
    ren_par.statistics_window_parameters.posY = parseUnsignedInt(string_value);
  } else if (key == "statistics_window_fps") {
    ren_par.statistics_window_parameters.fps = parseUnsignedInt(string_value);
  } else if (key == "font_path") {
    ren_par.font_path = string_value;
  } else if (key == "op_rad") {
    ren_par.op_rad = parseBool(string_value);
  } else {
    throw std::runtime_error{"Unknown render parameter " + key +
                             " at line: " + std::to_string(line_number) + "\n"};
  }
}
// Altra cosa da controllare, string_value che gli passo, è già la string più
// stretta che contiene l'informazione? non ci sono spazi od altre cose,
// problemi che possono comparire

void readWorldSection(WorldParams& wrld_par,
                      std::unordered_set<std::string>& initialized_keys,
                      std::string const& key, std::string const& string_value,
                      std::size_t line_number) {}

Config readParams(std::string const& path) {
  std::fstream filein(path);
  if (!filein) {
    throw std::runtime_error{"File could not be opened: " + path + "\n"};
  }

  Config parameters{};
  Section current_section = Section::none;

  std::unordered_set<std::string> simulation_keys;
  std::unordered_set<std::string> render_keys;
  std::unordered_set<std::string> world_keys;
  std::unordered_set<std::string> boids_keys;

  std::string line;

  std::size_t line_number{0};

  while (std::getline(filein, line)) {
    ++line_number;

    line = trimSpaces(line);

    if (line.empty() || line[0] == '#') {
      continue;
    }

    if (line == "[simulation]") {
      current_section = Section::simulation;
      continue;
    }
    if (line == "[render]") {
      current_section = Section::render;
      continue;
    }
    if (line == "[world]") {
      current_section = Section::world;
      continue;
    }
    if (line == "[boids]") {
      current_section = Section::boids;
      continue;
    }

    if (current_section == Section::none) {
      throw std::runtime_error{
          "non section-tag found before section-tag at line" +
          std::to_string(line_number) + "\n"};
    }

    std::string key;
    std::string string_value;

    try {
      parseKey(line, key, string_value);
    } catch (std::exception const& e) {
      throw std::runtime_error{"Error decyphering key at line: " +
                               std::to_string(line) + " : " + e.what() + "\n"}
    }

    switch (current_section) {
      case Section::simulation:
        readSimulationSection(parameters.sp, simulation_keys, key, string_value,
                              line_number);
        break;
      case Section::render:
        readRenderSection(parameters.rp, render_keys, key, string_value,
                          line_number);
        break;
      case Section::world:
        readWorldSection(parameters.wp, world_keys, key, string_value,
                         line_number);
        break;
      case Section::boids:
        readBoidSection(parameters.bp, boids_keys, key, string_value,
                        line_number);
        break;

      default:
        throw std::runtime_error("Invalid section argument \n");
    }
  }

  // È possibile che questo mi farà andare a dover modificare l'invarianza di
  // classe; l'invarianza di classe mi definisce una regola fondamentale che
  // ogni oggetto della classe mi deve andare a seguire dunque devo tornare a
  // controllare che effettivamente l'invarianza rispecchi la costruzione di uno
  // stato valido di un oggetto della classe dopo il costruttore; penso sia
  // meglio abbondare che togliere per l'invarianza di classe, essere più rigidi
  // subito che dover andare a stringere dopo; si fa sempre in tempo ad
  // allentare piuttosto che a stringere
  validateConfig(parameters);

  return parameters;
}

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
        string_value + " ; refer to the above instructions for typing. \n");
  }
  return value;
}

unsigned int parseUnsignedInt(std::string const& string_value) {
  std::size_t position{0};
  int value{std::stoi(string_value, &position)};
  if (position != string_value.size()) {
    throw std::runtime_error(
        "Invalid unsigned integer value (remove characters near numbers): " +
        string_value + " ; refer to the above instructions for typing. \n");
  }
  if (value >= 0) {
    return value;
  } else {
    return static_cast<unsigned int>(-value);
  }
}

double parseDouble(std::string const& string_value) {
  std::size_t position{0};
  double value{std::stod(string_value, &position)};
  if (position != string_value.size()) {
    throw std::runtime_error(
        "Invalid double value (remove characters near numbers): " +
        string_value + " ; refer to the above instructions for typing. \n");
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
                           " ; refer to the above instructions for typing. \n");
}

Config readSimulationParams(std::string const& path) {
  // Nei parametri descrittivi qua ha senso avere std::string const&?
  std::unordered_set<std::string, bool> initialized_values{
      {"non_pred_boidnum", false}, {"pred_boidnum", false}, {"dt", false}, {}};
  std::fstream filein(path);
  if (!filein) {
    throw std::runtime_error("File could not be opened: " + path);
  }
  Config parameters;

  std::string line;

  // This basically says that while i can get line from filein I'll put it into
  // line (look up reference better) when it cannot read a line anymore it stops
  while (std::getline(filein, line)) {
    line = trimSpaces(line);

    if (line.empty() || line[0] == '#') {
      continue;
    }

    // La domanda principale ho idea sia: voglio che il file di configurazione
    // sia molto rigido ma efficente e dunque o è come lo chiedo o la
    // simulazione non va? oppure voglio poter trovare ogni key in tutto il file
    // ma dovendo reiterare nel file tante volte? Rigido, altrimenti è veramente
    // lungo
    // Ho idea tocchi farlo con un unordered set,

    std::size_t equal_position{line.find('=')};
    std::size_t colon_position{line.find(':')};

    if (equal_position == std::string::npos &&
        colon_position == std::string::npos) {
      throw std::runtime_error(
          "This line is not empty but it doesn't have an equal or colon "
          "delimiter: " +
          line + "\n");
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

    // C'è un modo migliore di fare questo che una catena di else if, anche
    // solo escludendo quelli già inseriti?

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
      parameters.dt = parseDouble(value);
    }
    // Render
    else if (key == "flockWindowTitle") {
      parameters.flockWindowTitle = value;
    } else if (key == "flockWindowWidth") {
      parameters.flockWindowWidth = parseInt(value);
    } else if (key == "flockWindowHeight") {
      parameters.flockWindowHeight = parseInt(value);
    } else if (key == "flockWindowPositionX") {
      parameters.flockWindowPositionX = parseInt(value);
    } else if (key == "flockWindowPositionY") {
      parameters.flockWindowPositionY = parseInt(value);
    } else if (key == "flockWindowFps") {
      parameters.flockWindowFps = parseInt(value);
    } else if (key == "statisticsWindowTitle") {
      parameters.statisticsWindowTitle = value;
    } else if (key == "statisticsWindowWidth") {
      parameters.statisticsWindowWidth = parseInt(value);
    } else if (key == "statisticsWindowHeight") {
      parameters.statisticsWindowHeight = parseInt(value);
    } else if (key == "statisticsWindowPositionX") {
      parameters.statisticsWindowPositionX = parseInt(value);
    } else if (key == "statisticsWindowPositionY") {
      parameters.statisticsWindowPositionY = parseInt(value);
    } else if (key == "statisticsWindowFps") {
      parameters.statisticsWindowFps = parseInt(value);
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
  // The window conditions rely heavily on the sfml framework, thus the
  // maximum dimensions depend on one's hardware specifications
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