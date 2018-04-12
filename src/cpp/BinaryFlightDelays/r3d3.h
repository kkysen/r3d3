//
// Created by Khyber on 4/5/2018.
//

#ifndef BINARYFLIGHTDELAYS_R3D3_H
#define BINARYFLIGHTDELAYS_R3D3_H


#include <cstdint>
#include <sstream>
#include <memory>

#include <emscripten/fetch.h>

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
    
    template <typename T>
    constexpr size_t numBits();
    
    template <typename Target, size_t bitSize = numBits<Target>(), typename Source = i64>
    Target narrowCast(const Source source);;
    
    template<typename T>
    std::ostream& operator<<(std::ostream& out, std::vector<T> a) noexcept;
    
    template<typename T, size_t N>
    std::ostream& operator<<(std::ostream& out, std::array<T, N> a) noexcept;
    
    const std::string DIR = "../../../data/flight-delays/";
    
    std::unique_ptr<std::istream> openFile(std::string path) noexcept(false);
    
    std::vector<std::string> readLines(std::istream& stream) noexcept;
    
    std::vector<std::string> readLines(std::string path) noexcept(false);
    
    std::vector<std::string> split(std::string s, char delimiter) noexcept;
    
};


#endif //BINARYFLIGHTDELAYS_R3D3_H
