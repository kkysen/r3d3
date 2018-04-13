cmake_minimum_required(VERSION 3.11)
project(BinaryFlightDelays)

set(CMAKE_CXX_STANDARD 17)

include_directories(/home/kkysen/workspace/emsdk/emscripten/1.37.36/system/include/)

add_executable(BinaryFlightDelays
        src/CompactFlights.cpp
        src/util/DynamicEnum.tcc
        src/util/DynamicEnum.h
        src/r3d3.cpp
        src/r3d3.tcc
        src/r3d3.h
        src/util/NumberRange.cpp
        src/util/NumberRange.tcc
        src/util/NumberRange.h
        src/RawStringFlight.cpp
        src/RawStringFlight.h
        src/RawFlight.cpp
        src/RawFlight.h
        src/CompactFlight.cpp
        src/CompactFlight.h
        src/Flights.cpp
        src/Flights.h
        src/Date.cpp
        src/Date.h
        src/Time.cpp
        src/Time.h
        src/util/Serializer.tcc
        src/util/Serializer.h
        src/Airport.cpp
        src/Airport.h
        src/GeoLocation.cpp
        src/GeoLocation.h
        src/Airline.cpp
        src/Airline.h
        src/util/Blob.cpp
        src/util/Blob.h
        src/util/string_utils.cpp src/util/string_utils.h)