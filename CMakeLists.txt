cmake_minimum_required(VERSION 3.14)
project(MAI_OOP_3)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(SOURCES
    lib/geometry/point/point.cpp
    lib/geometry/figure/figure.cpp
    lib/geometry/figures/pentagon.cpp
    lib/geometry/figures/hexagon.cpp
    lib/geometry/figures/octagon.cpp
)
add_library(geometry ${SOURCES})
target_include_directories(geometry PUBLIC
    lib/geometry
    lib/geometry/figures
    lib/geometry/point
    lib/geometry/figure
)

add_library(array lib/array/array.cpp)
target_link_libraries(array PUBLIC geometry)
target_include_directories(array PUBLIC lib/array lib/geometry/figure)

add_executable(figures_tests tests/tests.cpp)
target_link_libraries(figures_tests geometry array gtest_main)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC geometry array)

include(GoogleTest)
gtest_discover_tests(figures_tests)
