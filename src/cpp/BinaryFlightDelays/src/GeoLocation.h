//
// Created by Khyber on 4/8/2018.
//

#ifndef BINARYFLIGHTDELAYS_GEOLOCATION_H
#define BINARYFLIGHTDELAYS_GEOLOCATION_H

#include <ostream>

namespace r3d3 {
    
    class GeoLocation final {
    
    private:
        
        double _latitude;
        double _longitude;
        
        static double haversine(GeoLocation A, GeoLocation B) noexcept;
    
    public:
        
        GeoLocation(double latitude, double longitude) noexcept;
        
        static GeoLocation of(double latitude, double longitude) noexcept;
        
        double latitude() const noexcept;
        
        double longitude() const noexcept;
        
        double distanceTo(GeoLocation location) const noexcept;
        
        double operator-(GeoLocation location) const noexcept;
        
        friend std::ostream& operator<<(std::ostream& out, GeoLocation location);
        
    };
    
    std::ostream& operator<<(std::ostream& out, GeoLocation location);
    
};

#endif //BINARYFLIGHTDELAYS_GEOLOCATION_H
