import {GeoLocation} from "./GeoLocation";

export interface Airport {
    
    iataCode(): string;
    
    name(): string;
    
    city(): string;
    
    state(): string;
    
    country(): string;
    
    location(): GeoLocation;
    
    distanceTo(airport: Airport): number;
    
}