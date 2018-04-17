//
// Created by Khyber on 4/8/2018.
//

#include "GeoLocation.h"
#include "r3d3.h"

#include <cmath>
#include <iostream>

namespace r3d3 {
    
    GeoLocation::GeoLocation(const double latitude, const double longitude) noexcept
            : _latitude(latitude), _longitude(longitude) {}
    
    GeoLocation GeoLocation::of(double latitude, double longitude) noexcept {
        return GeoLocation(latitude, longitude);
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
        return out << "(" << location._latitude << ", " << location._longitude << ")";
    }
    
};