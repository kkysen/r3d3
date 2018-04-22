//
// Created by Khyber on 4/20/2018.
//

#ifndef BINARYFLIGHTDELAYS_POINT_H
#define BINARYFLIGHTDELAYS_POINT_H

#include "../r3d3.h"

namespace r3d3 {
    
    struct Vector final {

    public:
        
        f32 x;
        f32 y;
        
        Vector operator+(Vector v) const noexcept;
    
        Vector operator-() const noexcept;
        
        Vector operator-(Vector v) const noexcept;
        
        Vector operator*(f32 scale) const noexcept;
        
        friend Vector operator*(f32 scale, Vector v) noexcept;
        
        // dot product, cross product not defined for 2D vectors
        f32 operator*(Vector v) const noexcept;
        
        bool hasNaN() const noexcept;
        
        friend std::ostream& operator<<(std::ostream& out, Vector vector) noexcept;
        
    };
    
};

#endif //BINARYFLIGHTDELAYS_POINT_H
