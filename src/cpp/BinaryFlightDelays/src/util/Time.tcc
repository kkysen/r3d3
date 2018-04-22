//
// Created by Khyber on 4/19/2018.
//

#include "Time.h"

namespace r3d3 {
    
    template <typename T>
    Time Time::operator*(T scale) const noexcept {
        return Time(static_cast<i16>(minute * scale));
    }
    
}
