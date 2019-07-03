cmake_minimum_required(VERSION 3.12)
project(IndividualProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(IndividualProject main.cpp Map.hpp Map.cpp Chromosome.cpp Chromosome.hpp  Tournament.hpp Tournament.cpp)