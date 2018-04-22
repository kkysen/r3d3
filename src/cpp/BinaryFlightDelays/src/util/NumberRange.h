//
// Created by Khyber on 4/5/2018.
//

#ifndef BINARYFLIGHTDELAYS_NUMBERRANGE_H
#define BINARYFLIGHTDELAYS_NUMBERRANGE_H

#include <ostream>

#include "../r3d3.h"

namespace r3d3 {
    
    struct NumberRange {
        
        const i64 min;
        const i64 max;
        
        u8 toNumBits() const noexcept;
        
        template<typename T>
//        using Mapper = i64 (*)(T);
        static NumberRange ofValues(std::vector<T> values, i64 (* mapper)(T)) noexcept;
        
        friend std::ostream& operator<<(std::ostream& out, NumberRange range) noexcept;
        
    };
    
};

#include "NumberRange.tcc"

#endif //BINARYFLIGHTDELAYS_NUMBERRANGE_H
