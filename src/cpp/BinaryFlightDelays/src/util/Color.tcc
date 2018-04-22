//
// Created by Khyber on 4/19/2018.
//

#include "Color.h"

namespace r3d3 {
    
    template <typename T>
    Color Color::operator*(const T scale) const noexcept {
        return {
                .r = static_cast<u8>(r * scale),
                .g = static_cast<u8>(g * scale),
                .b = static_cast<u8>(b * scale),
        };
    }
    
}
