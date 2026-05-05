cmake_minimum_required(VERSION 3.10.0)
project(flocksim VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# abilita warning
string(APPEND CMAKE_CXX_FLAGS
      " -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion"
      " -Wshadow -Wimplicit-fallthrough -Wextra-semi -Wold-style-cast"
      " -fno-omit-frame-pointer")

# abilita asserzioni della standard library
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  string(APPEND CMAKE_CXX_FLAGS " -D_GLIBCXX_ASSERTIONS")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  string(APPEND CMAKE_CXX_FLAGS " -D_LIBCPP_HARDENING_MODE=_LIBCPP_HARDENING_MODE_EXTENSIVE")
endif()

# abilita address sanitizer e undefined-behaviour sanitizer in Debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined")
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  string(APPEND CMAKE_CXX_FLAGS " -D_GLIBCXX_SANITIZE_STD_ALLOCATOR")
endif()
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined")

find_package(SFML 2 REQUIRED COMPONENTS graphics window system)

add_executable(flocksim src/main.cpp src/V2D.cpp src/Boid.cpp src/Input.cpp src/Rand.cpp src/Render.cpp src/VChange.cpp)


target_include_directories(flocksim PRIVATE include)
target_link_libraries(flocksim PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)


if (BUILD_TESTING)

  # aggiungi l'eseguibile progetto.t
  add_executable(flocksim.t test/boid.test.cpp src/Boid.cpp src/V2D.cpp)
  target_include_directories(flocksim.t PRIVATE ${CMAKE_SOURCE_DIR}/include)
  # aggiungi l'eseguibile progetto.t alla lista dei test
  add_test(NAME flockism.t COMMAND flocksim.t)

endif()