import {Airline} from "./Airline";
import {Airport} from "./Airport";
import {Time} from "./Time";
import {Date} from "./Date";


export interface FlightSide {
    
    time(): Time;
    
    scheduledTime(): Time;
    
    delay(): Time;
    
    airport(): Airport;
    
}

export type Departure = FlightSide;

export type Arrival = FlightSide;

export interface Flight {
    
    date(): Date;
    
    airline(): Airline;
    
    departure(): Departure;
    
    arrival(): Arrival;
    
    duration(): Time;
    
    scheduledDuration(): Time;
    
    distance(): number;
    
}