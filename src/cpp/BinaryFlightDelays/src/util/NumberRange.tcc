//
// Created by Khyber on 4/12/2018.
//

#include "NumberRange.h"

namespace r3d3 {
    
    template <typename T>
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
    
};