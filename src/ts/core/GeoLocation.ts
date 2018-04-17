export interface GeoLocation {

    latitude(): number;
    
    longitude(): number;
    
    distanceTo(location: GeoLocation): number;

}