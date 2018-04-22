//
// Created by Khyber on 4/19/2018.
//

#ifndef BINARYFLIGHTDELAYS_COLOR_H
#define BINARYFLIGHTDELAYS_COLOR_H

#include "../r3d3.h"

namespace r3d3 {
    
    struct Color final {
    
    public:
        
        u8 r;
        u8 g;
        u8 b;
        
        Color operator+(Color color) const noexcept;
        
        template <typename T>
        Color operator*(T scale) const noexcept;
        
        std::string rgbString() const noexcept;
        
        static Color mix(float weight1, Color color1, Color color2) noexcept;
        
        static const Color RED;
        static const Color GREEN;
        
    };
    
};

#include "Color.tcc"

#endif //BINARYFLIGHTDELAYS_COLOR_H
