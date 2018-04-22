//
// Created by Khyber on 4/19/2018.
//

#include "Color.h"

#include <cmath>

namespace r3d3 {
    
    Color Color::operator+(const Color color) const noexcept {
        return {
                .r = static_cast<u8>(r + color.r),
                .g = static_cast<u8>(g + color.g),
                .b = static_cast<u8>(b + color.b),
        };
    }
    
    Color Color::mix(float weight1, const Color color1, const Color color2) noexcept {
        weight1 = fminf(weight1, 255);
        weight1 = fmaxf(weight1, 0);
        const float weight2 = 1 - weight1;
        return color1 * weight1 + color2 * weight2;
    }
    
    std::string Color::rgbString() const noexcept {
        std::stringstream ss;
        ss << "rgb(" << r << "," << g << "," << b << ")";
        return ss.str();
    }
    
    const Color Color::RED = {255, 0, 0};
    const Color Color::GREEN = {0, 255, 0};
    
};