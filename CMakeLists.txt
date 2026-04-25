cmake_minimum_required(VERSION 3.10.0)
project(flocksim VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(flocksim src/main.cpp src/V2D.cpp src/Boid.cpp src/Input.cpp src/Rand.cpp src/Render.cpp src/VChange.cpp)

find_package(SFML 2 REQUIRED COMPONENTS graphics window system)

target_include_directories(flocksim PRIVATE include)
target_link_libraries(flocksim PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)


include(CTest)
enable_testing()
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)