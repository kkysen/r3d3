//
// Created by Khyber on 4/5/2018.
//

#ifndef BINARYFLIGHTDELAYS_R3D3_H
#define BINARYFLIGHTDELAYS_R3D3_H


#include <cstdint>

#include "DynamicEnum.h"

#define p(x) std::cout << #x << ": " << (x) << std::endl

namespace r3d3 {
    
    //    using u8 = uint8_t;
//    using u16 = uint16_t;
//    using u32 = uint32_t;
//    using u64 = uint64_t;
//
//    using i8 = int8_t;
//    using i16 = int16_t;
//    using i32 = int32_t;
//    using i64 = ino64_t;
    
    typedef uint8_t u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;
    
    typedef int8_t i8;
    typedef int16_t i16;
    typedef int32_t i32;
    typedef int64_t i64;
    
    template<typename T>
    std::ostream& operator<<(std::ostream& out, std::vector<T> a) noexcept;
    
    template<typename T, size_t N>
    std::ostream& operator<<(std::ostream& out, std::array<T, N> a) noexcept;
    
    template <typename T>
    void put(std::streambuf& buf, T t) noexcept;
    
    template <typename T>
    T get(std::streambuf& buf) noexcept;
    
    const std::string DIR = "../../../data/flight-delays/";
    const std::string AIRLINES_PATH = DIR + "airlines.csv";
    const std::string AIRPORTS_PATH = DIR + "airports.csv";
    const std::string FLIGHTS_PATH = DIR + "flights.csv";
    
    using Airlines = DynamicEnum<u8>;
    using Airports = DynamicEnum<u16>;
    
    using Airline = Airlines::size_type;
    using Airport = Airports::size_type;
    
    const Airlines AIRLINES = DynamicEnum<Airline>::ofCsv(AIRLINES_PATH);
    const Airports AIRPORTS = DynamicEnum<Airport>::ofCsv(AIRPORTS_PATH);
    
    std::istream& openFile(std::string path) noexcept(false);
    
    std::vector<std::string> readLines(std::istream& stream) noexcept;
    
    std::vector<std::string> readLines(std::string path) noexcept(false);
    
};


#endif //BINARYFLIGHTDELAYS_R3D3_H
