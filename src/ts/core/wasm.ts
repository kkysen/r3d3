import {Airport} from "./Airport";
import {Airline} from "./Airline";
import {DynamicEnum} from "./DynamicEnum";
import {flights, Flights} from "./Flights";
import {CircleSelection, GeoLocation} from "./GeoLocation";
import {Date} from "./Date";
import {GetArray} from "./GetArray";
import {Time} from "./Time";
import {Map} from "./map";

interface FlightsModule extends Module {
    
    readonly Flights: {
        
        create(data: Uint8Array): Flights;
        
    };
    
    readonly Airport: DynamicEnum<Airport> & {
        
        numAirports(): number;
        
        airports(): Airport[];
        
        ofIataCode(iataCode: string): Airport;
        
        plotAll(): CircleSelection[];
        
    };
    
    readonly Airline: DynamicEnum<Airline> & {
        
        numAirlines(): number;
        
        airlines(): Airline[];
        
    };
    
    readonly GeoLocation: {
        
        of(latitude: number, longitude: number): GeoLocation;
        
        // deprecated
        setScaleContinentalUS(width: number, height: number): void;
        
    };
    
    readonly Date: {
        
        of(dayOfYear: number): Date;
        
    };
    
    readonly Time: {
        
        of(minuteOfDay: number): Time;
        
    };
    
    readonly Map: Map,
    
}

export let Module: FlightsModule = undefined;

export const runAfterWasm = function <T>(func: () => T): Promise<T> {
    // console.log(func);
    Module = Module || (<any> window).Module;
    return new Promise(resolve => {
        const wrapper = function() {
            resolve(func());
        };
        if (Module.Flights) {
            wrapper();
        } else {
            Module.postRun.push(wrapper);
        }
    });
};

const extendInterfaces = function(Module: FlightsModule) {
    DynamicEnum.extendOn(Module.Airport, "airports");
    DynamicEnum.extendOn(Module.Airline, "airlines");
    
    (<any> Module).Map = Map;
    GeoLocation.extendOn(Module.GeoLocation.of(0, 0));
};

export const extendFlightsInterfaces = function() {
    GetArray.extendOn(flights);
    GetArray.extendOn(flights.get(0));
};

export const postWasm = function(): void {
    // console.log("postWasm");
    
    extendInterfaces(Module);
};