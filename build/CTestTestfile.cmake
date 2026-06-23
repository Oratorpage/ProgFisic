# CMake generated Testfile for 
# Source directory: /home/g042/FISICA/Progetti/ProgFisic
# Build directory: /home/g042/FISICA/Progetti/ProgFisic/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(flockism.t "/home/g042/FISICA/Progetti/ProgFisic/build/Debug/flocksim.t")
  set_tests_properties(flockism.t PROPERTIES  _BACKTRACE_TRIPLES "/home/g042/FISICA/Progetti/ProgFisic/CMakeLists.txt;52;add_test;/home/g042/FISICA/Progetti/ProgFisic/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(flockism.t "/home/g042/FISICA/Progetti/ProgFisic/build/Release/flocksim.t")
  set_tests_properties(flockism.t PROPERTIES  _BACKTRACE_TRIPLES "/home/g042/FISICA/Progetti/ProgFisic/CMakeLists.txt;52;add_test;/home/g042/FISICA/Progetti/ProgFisic/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(flockism.t "/home/g042/FISICA/Progetti/ProgFisic/build/RelWithDebInfo/flocksim.t")
  set_tests_properties(flockism.t PROPERTIES  _BACKTRACE_TRIPLES "/home/g042/FISICA/Progetti/ProgFisic/CMakeLists.txt;52;add_test;/home/g042/FISICA/Progetti/ProgFisic/CMakeLists.txt;0;")
else()
  add_test(flockism.t NOT_AVAILABLE)
endif()
