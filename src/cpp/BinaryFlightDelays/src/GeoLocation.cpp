//
// Created by Khyber on 4/8/2018.
//

#include "GeoLocation.h"
#include "r3d3.h"

#include <cmath>
#include <iostream>

namespace r3d3 {
    
    GeoLocation::GeoLocation(double longitude, double latitude) noexcept
            : _longitude(longitude), _latitude(latitude) {}
    
    GeoLocation GeoLocation::of(double longitude, double latitude) noexcept {
        return GeoLocation(longitude, latitude);
    }
    
    double GeoLocation::latitude() const noexcept {
        return _latitude;
    }
    
    double GeoLocation::longitude() const noexcept {
        return _longitude;
    }
    
    const double PI = M_PI;
    
    double degToRad(const double degrees) noexcept {
        return degrees * PI / 180;
    }
    
    const double EARTH_RADIUS = 6371e3;
    
    double square(const double x) noexcept {
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
    double GeoLocation::haversine(const GeoLocation A, const GeoLocation B) noexcept {
        const double lat1 = A._latitude;
        const double lon1 = A._longitude;
        
        const double lat2 = B._latitude;
        const double lon2 = B._longitude;
        
        const double phi1 = degToRad(lat1);
        const double phi2 = degToRad(lat2);
        const double deltaPhi = phi2 - phi1; // TODO check
        const double deltaLambda = degToRad(lon2 - lon1);
        
        const double a = square(sin(deltaPhi * 0.5))
                         + cos(phi1) * cos(phi2) * square(sin(deltaLambda * 0.5));
        const double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        const double R = EARTH_RADIUS;
        const double d = R * c;
        return d;
    }
    
    double GeoLocation::distanceTo(const GeoLocation location) const noexcept {
        return haversine(*this, location);
    }
    
    double GeoLocation::operator-(const GeoLocation location) const noexcept {
        return distanceTo(location);
    }
    
    std::ostream& operator<<(std::ostream& out, GeoLocation location) {
        return out << "(" << location._longitude << ", " << location._latitude << ")";
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
    
    GeoLocation operator/(double scale, GeoLocation location) noexcept {
        return GeoLocation(scale / location._longitude, scale / location._latitude);
    }
    
    GeoLocation GeoLocation::scale() const noexcept {
        return (*this + offset) * invSize * mapSize;
    }
    
    double GeoLocation::x() const noexcept {
        return scale()._longitude;
    }
    
    double GeoLocation::y() const noexcept {
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
    
    void GeoLocation::setScale(double width, double height,
                               GeoLocation NW, GeoLocation NE,
                               GeoLocation SW, GeoLocation SE) noexcept {
        // TODO
    }
    
    void GeoLocation::setScaleContinentalUS(double width, double height) noexcept {
        GeoLocation offset(+124.456890, -26.044343);
        GeoLocation size(+57.0530243, +22.97928);
        GeoLocation mapSize(width, height);
        setScale(offset, size, mapSize);
    }
    
};