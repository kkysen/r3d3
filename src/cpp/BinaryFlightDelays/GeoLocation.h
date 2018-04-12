//
// Created by Khyber on 4/8/2018.
//

#ifndef BINARYFLIGHTDELAYS_GEOLOCATION_H
#define BINARYFLIGHTDELAYS_GEOLOCATION_H

namespace r3d3 {
    
    class GeoLocation final {
    
    private:
        
        const double _latitude;
        const double _longitude;
        
        static double haversine(GeoLocation A, GeoLocation B);
    
    public:
        
        GeoLocation(double latitude, double longitude) noexcept;
        
        double latitude() const noexcept;
        
        double longitude() const noexcept;
        
        double distanceTo(GeoLocation location) const noexcept;
        
        double operator-(GeoLocation location) const noexcept;
        
    };
    
};

#endif //BINARYFLIGHTDELAYS_GEOLOCATION_H
