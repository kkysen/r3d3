//
// Created by Khyber on 4/5/2018.
//

#include "NumberRange.h"

#include <cmath>

namespace r3d3 {
    
    u8 NumberRange::toNumBits() const noexcept {
        const u64 maxAbs = static_cast<u64>(max - min);
        const u8 numBits = static_cast<u8>(ceil(log2(maxAbs)));
        return numBits;
    }
    
    std::ostream& operator<<(std::ostream& out, NumberRange range) noexcept {
        return out << "Range[" << range.min << ", " << range.max << "]";
    }
    
};