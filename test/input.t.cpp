#include "input.hpp"

#include "doctest.h"

TEST_CASE("Trim spaces") {
  std::string phrase{
      "            Oggi sono andato al mare ed è stato molto bello   "};
  std::string final_phrase{bs::trimSpaces(phrase)};
  CHECK(final_phrase == "Oggi sono andato al mare ed è stato molto bello");
}
TEST_CASE("Parsing integers") {
  // Should succeed
  std::string phrase1{"100"};
  int value1{bs::parseInt(phrase1)};
  CHECK(value1 == 100);
  // Should succeed
  std::string phrase2{"-100"};
  int value2{bs::parseInt(phrase2)};
  CHECK(value2 == -100);
  // Should throw
  std::string phrase3{"banana"};
  CHECK_THROWS(bs::parseInt(phrase3));
  // Should throw
  std::string phrase4{"100.245"};
  CHECK_THROWS(bs::parseInt(phrase4));
  // Should throw
  std::string phrase5{"  145    "};
  CHECK_THROWS(bs::parseInt(phrase5));
}
TEST_CASE("Parsing unsigned integers") {
  // Should succeed
  std::string phrase1{"809070605"};
  unsigned int value1{bs::parseUnsignedInt(phrase1)};
  CHECK(value1 == 809070605);
  // Should succeed
  std::string phrase2{"-809070605"};
  unsigned int value2{bs::parseUnsignedInt(phrase2)};
  CHECK(value2 == 809070605);
  // Should throw, too large
  std::string phrase3{"8090706050"};
  CHECK_THROWS(bs::parseUnsignedInt(phrase3));
  // Should throw
  std::string phrase4{"banana"};
  CHECK_THROWS(bs::parseUnsignedInt(phrase4));
  // Should throw
  std::string phrase5{"100.245"};
  CHECK_THROWS(bs::parseUnsignedInt(phrase5));
  // Should throw
  std::string phrase6{"  145    "};
  CHECK_THROWS(bs::parseUnsignedInt(phrase6));
}
TEST_CASE("Parsing doubles") {
  // Should succeed
  std::string phrase1{"200.456"};
  double value1{bs::parseDouble(phrase1)};
  CHECK(value1 == 200.456);
  // Should succeed
  std::string phrase2{"-200.456"};
  double value2{bs::parseDouble(phrase2)};
  CHECK(value2 == -200.456);
  // Should throw
  std::string phrase3{"banana"};
  CHECK_THROWS(bs::parseUnsignedInt(phrase3));
  // Should throw
  std::string phrase4{"  145    "};
  CHECK_THROWS(bs::parseUnsignedInt(phrase4));
}
TEST_CASE("Parsing bools") {
  // Should throw
  std::string phrase1{"200.456"};
  CHECK_THROWS(bs::parseBool(phrase1));
  // Should throw
  std::string phrase2{"-200.456"};
  CHECK_THROWS(bs::parseBool(phrase2));
  // Should throw
  std::string phrase3{"banana"};
  CHECK_THROWS(bs::parseUnsignedInt(phrase3));
  // Should throw
  std::string phrase4{"  145    "};
  CHECK_THROWS(bs::parseUnsignedInt(phrase4));
  // Should succeed
  std::string phrase5{"true"};
  bool value5{bs::parseBool(phrase5)};
  CHECK(value5 == true);
  // Should succeed
  std::string phrase6{"false"};
  bool value6{bs::parseBool(phrase6)};
  CHECK(value6 == false);
}
TEST_CASE("Reading parameters structure") {
  CHECK_THROWS(bs::readParams("banana"));
  // Should all throw up to 4, no section tags
  CHECK_THROWS(bs::readParams("config_tests/testfile1.txt"));
  CHECK_THROWS(bs::readParams("config_tests/testfile2.txt"));
  CHECK_THROWS(bs::readParams("config_tests/testfile3.txt"));
  CHECK_THROWS(bs::readParams("config_tests/testfile4.txt"));

  CHECK_NOTHROW(bs::readParams("config_tests/testfile5.txt"));
  // Missing equal sign
  CHECK_THROWS(bs::readParams("config_tests/testfile6.txt"));
  // Duplicate parameter initialization
  CHECK_THROWS(bs::readParams("config_tests/testfile7.txt"));
  // Unknown parameter
  CHECK_THROWS(bs::readParams("config_tests/testfile8.txt"));
  // Unknown section
  CHECK_THROWS(bs::readParams("config_tests/testfile9.txt"));
}
// CHECK(configuration.);
TEST_CASE("Reading parameters output") {
  bs::Config configuration{bs::readParams("config_tests/testfile10.txt")};
  CHECK(configuration.sp.non_pred_boidnum == 350);
  CHECK(configuration.sp.pred_boidnum == 20);
  CHECK(configuration.sp.dt == 0.01);

  CHECK(configuration.rp.flock_window_parameters.title == "Simulation Window");
  CHECK(configuration.rp.flock_window_parameters.width == 800);
  CHECK(configuration.rp.flock_window_parameters.height == 600);
  CHECK(configuration.rp.flock_window_parameters.posX == 750);
  CHECK(configuration.rp.flock_window_parameters.posY == 200);
  CHECK(configuration.rp.flock_window_parameters.fps == 60);

  CHECK(configuration.rp.statistics_window_parameters.title ==
        "Statistics Window");
  CHECK(configuration.rp.statistics_window_parameters.width == 500);
  CHECK(configuration.rp.statistics_window_parameters.height == 700);
  CHECK(configuration.rp.statistics_window_parameters.posX == 50);
  CHECK(configuration.rp.statistics_window_parameters.posY == 50);
  CHECK(configuration.rp.statistics_window_parameters.fps == 120);

  CHECK(configuration.rp.font_path == "config/DejaVuSans.ttf");
  CHECK(configuration.rp.op_rad == false);

  CHECK(configuration.wp.dimensions.x == 800);
  CHECK(configuration.wp.dimensions.y == 600);
  CHECK(configuration.wp.toroidal == false);

  CHECK(configuration.bp.detection_radius == 70);
  CHECK(configuration.bp.danger_radius == 30);
  CHECK(configuration.bp.angle_of_view == 360);
  CHECK(configuration.bp.max_speed == 2500);
  CHECK(configuration.bp.min_speed == 2);
  CHECK(configuration.bp.separation == doctest::Approx(0.07).epsilon(0.001));
  CHECK(configuration.bp.alignment == doctest::Approx(0.04).epsilon(0.001));
  CHECK(configuration.bp.cohesion == doctest::Approx(0.05).epsilon(0.001));
}
