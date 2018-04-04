cmake_minimum_required(VERSION 3.5)
project(DsvMissingDataStats)

set(CMAKE_CXX_STANDARD 17)

add_executable(DsvMissingDataStats main.cpp DsvMissingDataStats.cpp DsvMissingDataStats.h utils.cpp utils.h)