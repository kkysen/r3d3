//
// Created by Khyber on 4/5/2018.
//

#include <cmath>
#include "NumberRange.h"

using namespace r3d3;

u8 NumberRange::toNumBits() const noexcept {
    const u64 maxAbs = static_cast<u64>(max - min);
    return static_cast<u8>(log2(maxAbs));
}

template<typename T>
NumberRange NumberRange::ofValues(const std::vector<T> values, i64 (* const mapper)(T)) noexcept {
    const i64 first = mapper(values[0]);
    i64 min = first;
    i64 max = first;
    for (auto&& value : values) {
        const i64 n = mapper(value);
        if (n < min) {
            min = n;
        } else if (n > max) {
            max = n;
        }
    }
    return {
            .min = min,
            .max = max,
    };
}

std::ostream& operator<<(std::ostream& out, NumberRange range) noexcept {
    return out << "Range[" << range.min << ", " << range.max << "]";
}