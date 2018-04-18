export interface GeoLocation {
    
    longitude(): number;
    
    latitude(): number;
    
    scale(): GeoLocation;
    
    x(): number;
    
    y(): number;
    
    distanceTo(location: GeoLocation): number;

}