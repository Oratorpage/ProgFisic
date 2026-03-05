cmake_minimum_required(VERSION 3.10.0)
project(ProgFisic VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ProgFisic main.cpp)

find_package(SFML 2 REQUIRED COMPONENTS graphics window system audio)

target_link_libraries(ProgFisic PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)


include(CTest)
enable_testing()
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)