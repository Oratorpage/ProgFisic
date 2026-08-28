#include "input.hpp"

#include <fstream>
#include <stdexcept>

namespace bs {

enum class Section { none, simulation, render, world, boids };

std::string trimSpaces(std::string const& line) {
  std::size_t first{0};
  while (first < line.size() && (line[first] == ' ' || line[first] == '\t')) {
    ++first;
  }
  std::size_t last{line.size()};
  while (last > first && (line[last - 1] == ' ' || line[last - 1] == '\t')) {
    --last;
  }

  return line.substr(first, last - first);
  // according to documentation if pos is equal to string length it returns an
  // empty string; if pos bigger than string legth then it throws out of range
}

int parseInt(std::string const& string_value) {
  std::size_t position{0};
  int value;

  try {
    value = std::stoi(string_value, &position);
  } catch (...) {
    throw std::runtime_error{"Expected an integer, found: " + string_value +
                             "\n"};
  }
  // This if below invalidates the useful propriety of std::stoi which allows to
  // eliminate whitespace characters near the number in string form that needs
  // to be converted; I preferred a harder approach at first being my first time
  // making something like this, it avoids false positives which are quite
  // annoying to diagnose
  if (position != string_value.size()) {
    throw std::runtime_error(
        "Invalid integer value (remove characters near numbers): " +
        string_value + " ; refer to the above instructions for typing. \n");
  }
  return value;
}

// Converts the negative values passed into positives as a way to parse for
// certain purposes and avoid narrowind; need careful usage as is not standard
unsigned int parseUnsignedInt(std::string const& string_value) {
  std::size_t position{0};

  int value;
  try {
    value = std::stoi(string_value, &position);
  } catch (...) {
    throw std::runtime_error{
        "Expected an unsigned integer, found: " + string_value + "\n"};
  }
  if (position != string_value.size()) {
    throw std::runtime_error(
        "Invalid unsigned integer value (remove characters near numbers): " +
        string_value + " ; refer to the above instructions for typing. \n");
  }
  if (value >= 0) {
    return static_cast<unsigned int>(value);
  } else {
    return static_cast<unsigned int>(-value);
  }
}

double parseDouble(std::string const& string_value) {
  std::size_t position{0};
  double value;
  try {
    value = std::stod(string_value, &position);
  } catch (...) {
    throw std::runtime_error{"Expected a double, found: " + string_value +
                             "\n"};
  }
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

void readSimulationSection(SimParams& sim_par,
                           std::unordered_set<std::string>& initialized_keys,
                           std::string const& key,
                           std::string const& string_value,
                           std::size_t line_number) {
  if (!initialized_keys.insert(key).second) {
    throw std::runtime_error{"Duplicate simulation parameter key: " + key +
                             " at line: " + std::to_string(line_number) + "\n"};
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
    throw std::runtime_error{"Duplicate render parameter key: " + key +
                             " at line: " + std::to_string(line_number) + "\n"};
  } else if (key == "flock_window_title") {
    ren_par.flock_window_parameters.title = string_value;
  } else if (key == "flock_window_width") {
    ren_par.flock_window_parameters.width = parseUnsignedInt(string_value);
  } else if (key == "flock_window_height") {
    ren_par.flock_window_parameters.height = parseUnsignedInt(string_value);
  } else if (key == "flock_window_posX") {
    ren_par.flock_window_parameters.posX = parseInt(string_value);
  } else if (key == "flock_window_posY") {
    ren_par.flock_window_parameters.posY = parseInt(string_value);
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
    ren_par.statistics_window_parameters.posX = parseInt(string_value);
  } else if (key == "statistics_window_posY") {
    ren_par.statistics_window_parameters.posY = parseInt(string_value);
  } else if (key == "statistics_window_fps") {
    ren_par.statistics_window_parameters.fps = parseUnsignedInt(string_value);
  }

  else if (key == "font_path") {
    ren_par.font_path = string_value;
  } else if (key == "op_rad") {
    ren_par.op_rad = parseBool(string_value);
  }

  else {
    throw std::runtime_error{"Unknown render parameter: " + key +
                             " at line: " + std::to_string(line_number) + "\n"};
  }
}

void readWorldSection(WorldParams& wrld_par,
                      std::unordered_set<std::string>& initialized_keys,
                      std::string const& key, std::string const& string_value,
                      std::size_t line_number) {
  if (!initialized_keys.insert(key).second) {
    throw std::runtime_error{"Duplicate world parameter key: " + key +
                             " at line: " + std::to_string(line_number) + "\n"};
  } else if (key == "world_width") {
    wrld_par.dimensions.x = parseDouble(string_value);
  } else if (key == "world_height") {
    wrld_par.dimensions.y = parseDouble(string_value);
  } else if (key == "toroidal") {
    wrld_par.toroidal = parseBool(string_value);
  } else {
    throw std::runtime_error{"Unknown world parameter: " + key + " at  line: " +
                             std::to_string(line_number) + "\n"};
  }
}

void readBoidsSection(BoidProperties& boid_par,
                      std::unordered_set<std::string>& initialized_keys,
                      std::string const& key, std::string const& string_value,
                      std::size_t line_number) {
  if (!initialized_keys.insert(key).second) {
    throw std::runtime_error{"Duplicate Boid parameter key: " + key +
                             " at line: " + std::to_string(line_number) + "\n"};
  } else if (key == "detection_radius") {
    boid_par.detection_radius = parseDouble(string_value);
  } else if (key == "danger_radius") {
    boid_par.danger_radius = parseDouble(string_value);
  } else if (key == "angle_of_view") {
    boid_par.angle_of_view = parseDouble(string_value);
  } else if (key == "max_speed") {
    boid_par.max_speed = parseDouble(string_value);
  } else if (key == "min_speed") {
    boid_par.min_speed = parseDouble(string_value);
  } else if (key == "separation") {
    boid_par.separation = parseDouble(string_value);
  } else if (key == "alignment") {
    boid_par.alignment = parseDouble(string_value);
  } else if (key == "cohesion") {
    boid_par.cohesion = parseDouble(string_value);
  } else {
    throw std::runtime_error{"Unknown boid parameter: " + key +
                             " at line: " + std::to_string(line_number) + "\n"};
  }
}

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
          "Non section-tag found before section-tag at line: " +
          std::to_string(line_number) + "\n"};
    }

    std::string key;
    std::string string_value;

    try {
      extractKeyValue(line, key, string_value);

      switch (current_section) {
        case Section::simulation:
          readSimulationSection(parameters.sp, simulation_keys, key,
                                string_value, line_number);
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
          readBoidsSection(parameters.bp, boids_keys, key, string_value,
                           line_number);
          break;

        default:
          throw std::runtime_error("Invalid section argument \n");
      }
    } catch (std::exception const& e) {
      throw std::runtime_error{
          "Error decyphering key at line: " + std::to_string(line_number) +
          " : " + e.what() + "\n"};
    }
  }

  checkSimulationKeys(simulation_keys);
  checkRenderKeys(render_keys);
  checkWorldKeys(world_keys);
  checkBoidsKeys(boids_keys);

  return parameters;
}

void extractKeyValue(std::string const& line, std::string& key,
                     std::string& string_value) {
  std::size_t equal_position{line.find('=')};
  std::size_t colon_position{line.find(':')};

  if (colon_position == std::string::npos) {
    key = trimSpaces(line.substr(0, equal_position));
    string_value = trimSpaces(line.substr(equal_position + 1));
  } else if (equal_position == std::string::npos) {
    key = trimSpaces(line.substr(0, colon_position));
    string_value = trimSpaces(line.substr(colon_position + 1));
  } else {
    throw std::runtime_error{"No equal or colon found in line: " + line + "\n"};
  }

  if (key.empty()) {
    throw std::runtime_error{"Missing parameter key \n"};
  }
  if (string_value.empty()) {
    throw std::runtime_error{"Missing parameter value \n"};
  }
}

void checkSimulationKeys(
    std::unordered_set<std::string> const& initialized_keys) {
  if (initialized_keys.find("non_pred_boidnum") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [simulation]: non_pred_boidnum \n"};
  }
  if (initialized_keys.find("pred_boidnum") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [simulation]: pred_boidnum \n"};
  }
  if (initialized_keys.find("dt") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [simulation]: dt \n"};
  }
}

// I don't really like this humongous thing I've created, either with a lot more
// parameter passing or through the use of unordered_map it may come out better,
//  when I'll come back to implement the view and the rest of the things I'll
// also come back to better this
void checkRenderKeys(std::unordered_set<std::string> const& initialized_keys) {
  if (initialized_keys.find("flock_window_title") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [render]: flock_window_title \n"};
  }
  if (initialized_keys.find("flock_window_width") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [render]: flock_window_width \n"};
  }
  if (initialized_keys.find("flock_window_height") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [render]: flock_window_height \n"};
  }
  if (initialized_keys.find("flock_window_posX") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [render]: flock_window_posX \n"};
  }
  if (initialized_keys.find("flock_window_posY") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [render]: flock_window_posY \n"};
  }
  if (initialized_keys.find("flock_window_fps") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [render]: flock_window_fps \n"};
  }

  if (initialized_keys.find("statistics_window_title") ==
      initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [render]: statistics_window_title \n"};
  }
  if (initialized_keys.find("statistics_window_width") ==
      initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [render]: statistics_window_width \n"};
  }
  if (initialized_keys.find("statistics_window_height") ==
      initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [render]: statistics_window_height \n"};
  }
  if (initialized_keys.find("statistics_window_posX") ==
      initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [render]: statistics_window_posX \n"};
  }
  if (initialized_keys.find("statistics_window_posY") ==
      initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [render]: statistics_window_posY \n"};
  }
  if (initialized_keys.find("statistics_window_fps") ==
      initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [render]: statistics_window_fps \n"};
  }

  if (initialized_keys.find("font_path") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [render]: font_path \n"};
  }
  if (initialized_keys.find("op_rad") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [render]: op_rad \n"};
  }
}

void checkWorldKeys(std::unordered_set<std::string> const& initialized_keys) {
  if (initialized_keys.find("world_width") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [world]: world_width \n"};
  }
  if (initialized_keys.find("world_height") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [world]: world_height \n"};
  }
  if (initialized_keys.find("toroidal") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [world]: toroidal \n"};
  }
}

void checkBoidsKeys(std::unordered_set<std::string> const& initialized_keys) {
  if (initialized_keys.find("detection_radius") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [boids]: detection_radius \n"};
  }
  if (initialized_keys.find("danger_radius") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [boids]: danger_radius \n"};
  }
  if (initialized_keys.find("angle_of_view") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [boids]: angle_of_view \n"};
  }
  if (initialized_keys.find("max_speed") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [boids]: max_speed \n"};
  }
  if (initialized_keys.find("min_speed") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [boids]: min_speed \n"};
  }
  if (initialized_keys.find("separation") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [boids]: separation \n"};
  }
  if (initialized_keys.find("alignment") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [boids]: alignment \n"};
  }
  if (initialized_keys.find("cohesion") == initialized_keys.end()) {
    throw std::runtime_error{
        "Necessary key not initialized after reading from configuration file "
        "in section [boids]: cohesion \n"};
  }
}

}  // namespace bs