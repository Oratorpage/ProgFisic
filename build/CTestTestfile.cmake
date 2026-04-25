# CMake generated Testfile for 
# Source directory: /home/g042/FISICA/Progetti/ProgFisic
# Build directory: /home/g042/FISICA/Progetti/ProgFisic/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(progetto.t "/home/g042/FISICA/Progetti/ProgFisic/build/Debug/progetto.t")
  set_tests_properties(progetto.t PROPERTIES  _BACKTRACE_TRIPLES "/home/g042/FISICA/Progetti/ProgFisic/CMakeLists.txt;51;add_test;/home/g042/FISICA/Progetti/ProgFisic/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(progetto.t "/home/g042/FISICA/Progetti/ProgFisic/build/Release/progetto.t")
  set_tests_properties(progetto.t PROPERTIES  _BACKTRACE_TRIPLES "/home/g042/FISICA/Progetti/ProgFisic/CMakeLists.txt;51;add_test;/home/g042/FISICA/Progetti/ProgFisic/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(progetto.t "/home/g042/FISICA/Progetti/ProgFisic/build/RelWithDebInfo/progetto.t")
  set_tests_properties(progetto.t PROPERTIES  _BACKTRACE_TRIPLES "/home/g042/FISICA/Progetti/ProgFisic/CMakeLists.txt;51;add_test;/home/g042/FISICA/Progetti/ProgFisic/CMakeLists.txt;0;")
else()
  add_test(progetto.t NOT_AVAILABLE)
endif()
