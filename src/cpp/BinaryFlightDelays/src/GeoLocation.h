//
// Created by Khyber on 4/8/2018.
//

#ifndef BINARYFLIGHTDELAYS_GEOLOCATION_H
#define BINARYFLIGHTDELAYS_GEOLOCATION_H

#include <ostream>

namespace r3d3 {
    
    class GeoLocation final {
    
    private:
    
        double _longitude;
        double _latitude;
        
        static double haversine(GeoLocation A, GeoLocation B) noexcept;
    
    public:
        
        GeoLocation(double longitude, double latitude) noexcept;
        
        static GeoLocation of(double longitude, double latitude) noexcept;
    
        double longitude() const noexcept;
        
        double latitude() const noexcept;
        
        double distanceTo(GeoLocation location) const noexcept;
        
        double operator-(GeoLocation location) const noexcept;
        
        friend std::ostream& operator<<(std::ostream& out, GeoLocation location);

    private:
    
        GeoLocation operator-() const noexcept;
        
        GeoLocation operator+(GeoLocation location) const noexcept;
        
        GeoLocation operator*(GeoLocation location) const noexcept;
        
        friend GeoLocation operator/(double scale, GeoLocation location) noexcept;

    private:
        
        static GeoLocation offset;
        static GeoLocation invSize;
        static GeoLocation mapSize;
    
        static void setScale(GeoLocation offset, GeoLocation size, GeoLocation mapSize) noexcept;
        
    public:
        
        static void setScale(double width, double height,
                             GeoLocation northWest, GeoLocation northEast,
                             GeoLocation southWest, GeoLocation southEast) noexcept;
        
        static void setScaleContinentalUS(double width, double height) noexcept;
    
        GeoLocation scale() const noexcept;
        
        double x() const noexcept;
    
        double y() const noexcept;
        
    };
    
//    GeoLocation operator/(double scale, GeoLocation location) const noexcept;
    
    std::ostream& operator<<(std::ostream& out, GeoLocation location);
    
};

#endif //BINARYFLIGHTDELAYS_GEOLOCATION_H
