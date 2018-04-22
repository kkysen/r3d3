//
// Created by Khyber on 4/8/2018.
//

#include "GeoLocation.h"
#include "../r3d3.h"

#include <cmath>
#include <iostream>

namespace r3d3 {
    
    GeoLocation::GeoLocation(f64 longitude, f64 latitude) noexcept
            : _longitude(longitude), _latitude(latitude) {}
    
    GeoLocation GeoLocation::of(f64 longitude, f64 latitude) noexcept {
        return GeoLocation(longitude, latitude);
    }
    
    f64 GeoLocation::latitude() const noexcept {
        return _latitude;
    }
    
    f64 GeoLocation::longitude() const noexcept {
        return _longitude;
    }
    
    const f64 PI = M_PI;
    
    f64 degToRad(const f64 degrees) noexcept {
        return degrees * PI / 180;
    }
    
    const f64 EARTH_RADIUS = 6371e3;
    
    f64 square(const f64 x) noexcept {
        return x * x;
    }
    
    /**
     * Haversine's formula:	 a = sin²(Δφ/2) + cos φ1 ⋅ cos φ2 ⋅ sin²(Δλ/2)
     * c = 2 ⋅ atan2( √a, √(1−a) )
     * d = R ⋅ c
     * where
     *      φ is latitude,
     *      λ is longitude,
     *      R is earth’s radius (mean radius = 6,371km)
     *
     * @param A location A
     * @param B location B
     * @return the distance between A and B (in meters)
     */
    f64 GeoLocation::haversine(const GeoLocation A, const GeoLocation B) noexcept {
        const f64 lat1 = A._latitude;
        const f64 lon1 = A._longitude;
        
        const f64 lat2 = B._latitude;
        const f64 lon2 = B._longitude;
        
        const f64 phi1 = degToRad(lat1);
        const f64 phi2 = degToRad(lat2);
        const f64 deltaPhi = phi2 - phi1; // TODO check
        const f64 deltaLambda = degToRad(lon2 - lon1);
        
        const f64 a = square(sin(deltaPhi * 0.5))
                         + cos(phi1) * cos(phi2) * square(sin(deltaLambda * 0.5));
        const f64 c = 2 * atan2(sqrt(a), sqrt(1 - a));
        const f64 R = EARTH_RADIUS;
        const f64 d = R * c;
        return d;
    }
    
    f64 GeoLocation::distanceTo(const GeoLocation location) const noexcept {
        return haversine(*this, location);
    }
    
    f64 GeoLocation::operator-(const GeoLocation location) const noexcept {
        return distanceTo(location);
    }
    
    std::ostream& operator<<(std::ostream& out, GeoLocation location) {
        // "backwards" order b/c that's how latitude, longitude are normally written
        return out << "(" << location._latitude << ", " << location._longitude << ")";
    }
    
    //
    
    GeoLocation GeoLocation::operator-() const noexcept {
        return GeoLocation(-_longitude, -_latitude);
    }
    
    GeoLocation GeoLocation::operator+(GeoLocation location) const noexcept {
        return GeoLocation(_longitude + location._longitude, _latitude + location._latitude);
    }
    
    GeoLocation GeoLocation::operator*(GeoLocation location) const noexcept {
        return GeoLocation(_longitude * location._longitude, _latitude * location._latitude);
    }
    
    GeoLocation operator/(f64 scale, GeoLocation location) noexcept {
        return GeoLocation(scale / location._longitude, scale / location._latitude);
    }
    
    GeoLocation GeoLocation::scale() const noexcept {
        return (*this + offset) * invSize * mapSize;
    }
    
    f64 GeoLocation::x() const noexcept {
        return scale()._longitude;
    }
    
    f64 GeoLocation::y() const noexcept {
        return scale()._latitude;
    }
    
    GeoLocation GeoLocation::offset = GeoLocation(NAN, NAN);
    GeoLocation GeoLocation::invSize = GeoLocation(NAN, NAN);
    GeoLocation GeoLocation::mapSize = GeoLocation(NAN, NAN);
    
    void GeoLocation::setScale(GeoLocation offset, GeoLocation size, GeoLocation mapSize) noexcept {
        GeoLocation::offset = offset;
        GeoLocation::invSize = 1 / size;
        GeoLocation::mapSize = mapSize;
    }
    
    void GeoLocation::setScale(f64 width, f64 height,
                               GeoLocation NW, GeoLocation NE,
                               GeoLocation SW, GeoLocation SE) noexcept {
        // TODO
    }
    
    void GeoLocation::setScaleContinentalUS(f64 width, f64 height) noexcept {
        GeoLocation offset(+124.456890, -26.044343);
        GeoLocation size(+57.0530243, +22.97928);
        GeoLocation mapSize(width, height);
        setScale(offset, size, mapSize);
    }
    
};
