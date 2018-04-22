//
// Created by Khyber on 4/20/2018.
//

#include <cmath>
#include "Vector.h"

namespace r3d3 {
    
    Vector Vector::operator+(Vector v) const noexcept {
        return {x + v.x, y + v.y};
    }
    
    Vector Vector::operator-() const noexcept {
        return {-x, -y};
    }
    
    Vector Vector::operator-(Vector v) const noexcept {
        return *this + -v;
    }
    
    Vector Vector::operator*(f32 scale) const noexcept {
        return {scale * x, scale * y};
    }
    
    Vector operator*(f32 scale, Vector v) noexcept {
        return v * scale;
    }
    
    f32 Vector::operator*(Vector v) const noexcept {
        return x * v.x + y * v.y;
    }
    
    bool Vector::hasNaN() const noexcept {
        return std::isnan(x) || std::isnan(y);
    }
    
    std::ostream& operator<<(std::ostream& out, Vector v) noexcept {
        return out << "(" << v.x << ", " << v.y << ")";
    }
    
};