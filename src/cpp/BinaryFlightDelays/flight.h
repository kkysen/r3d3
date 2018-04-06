//
// Created by Khyber on 4/3/2018.
//

#ifndef BINARYFLIGHTDELAYS_FLIGHT_H
#define BINARYFLIGHTDELAYS_FLIGHT_H


#include <cstdint>
#include <string>
#include <vector>
#include <array>

#include "r3d3.h"
#include "DynamicEnum.h"
#include "NumberRange.h"
#include "RawStringFlight.h"

template<typename T, typename... A>
constexpr auto array_of(A&& ... a) -> std::array<T, sizeof...(A)> {
    return {{std::forward<A>(a)...}};
}

template<typename Target, typename Source>
Target narrow_cast(const Source source) {
    const auto target = static_cast<Target>(source);
    if (static_cast<Source>(target) != source) {
        throw std::runtime_error("narrow_cast<>() failed");
    }
}

namespace r3d3 {
    
    void f() {
        const Airport airport = AIRPORTS[""];
        const std::string airportName = AIRPORTS[airport];
    }
    
};


#endif //BINARYFLIGHTDELAYS_FLIGHT_H
