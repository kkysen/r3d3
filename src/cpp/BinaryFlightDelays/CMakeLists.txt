cmake_minimum_required(VERSION 3.11)
project(BinaryFlightDelays)

set(CMAKE_CXX_STANDARD 17)

include_directories(/home/kkysen/workspace/emsdk/emscripten/1.37.36/system/include/)

add_executable(BinaryFlightDelays
        main.cpp
        flight.cpp
        flight.h
        DynamicEnum.cpp
        DynamicEnum.h
        r3d3.cpp
        r3d3.h
        NumberRange.cpp
        NumberRange.h
        RawStringFlight.cpp
        RawStringFlight.h
        RawFlight.cpp
        RawFlight.h
        CompactFlight.cpp
        CompactFlight.h
        Flights.cpp Flights.h Date.cpp Date.h Time.cpp Time.h)