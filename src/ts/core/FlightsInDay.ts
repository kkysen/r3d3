import {Flight} from "./Flight";
import {GetArray} from "./GetArray";

export interface FlightsInDay extends GetArray<Flight> {
    
    numFlights(): number;
    
}