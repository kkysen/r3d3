//
// Created by Khyber on 4/8/2018.
//

#ifndef BINARYFLIGHTDELAYS_GEOLOCATION_H
#define BINARYFLIGHTDELAYS_GEOLOCATION_H

#include <ostream>
#include "../r3d3.h"

namespace r3d3 {
    
    class GeoLocation final {
    
    private:
    
        f64 _longitude;
        f64 _latitude;
        
        static f64 haversine(GeoLocation A, GeoLocation B) noexcept;
    
    public:
        
        GeoLocation(f64 longitude, f64 latitude) noexcept;
        
        static GeoLocation of(f64 longitude, f64 latitude) noexcept;
    
        f64 longitude() const noexcept;
        
        f64 latitude() const noexcept;
        
        f64 distanceTo(GeoLocation location) const noexcept;
        
        f64 operator-(GeoLocation location) const noexcept;
        
        friend std::ostream& operator<<(std::ostream& out, GeoLocation location);

    private:
    
        GeoLocation operator-() const noexcept;
        
        GeoLocation operator+(GeoLocation location) const noexcept;
        
        GeoLocation operator*(GeoLocation location) const noexcept;
        
        friend GeoLocation operator/(f64 scale, GeoLocation location) noexcept;

    private:
        
        static GeoLocation offset;
        static GeoLocation invSize;
        static GeoLocation mapSize;
    
        static void setScale(GeoLocation offset, GeoLocation size, GeoLocation mapSize) noexcept;
        
    public:
        
        static void setScale(f64 width, f64 height,
                             GeoLocation northWest, GeoLocation northEast,
                             GeoLocation southWest, GeoLocation southEast) noexcept;
        
        static void setScaleContinentalUS(f64 width, f64 height) noexcept;
    
        GeoLocation scale() const noexcept;
        
        f64 x() const noexcept;
    
        f64 y() const noexcept;
        
    };
    
};

#endif //BINARYFLIGHTDELAYS_GEOLOCATION_H
