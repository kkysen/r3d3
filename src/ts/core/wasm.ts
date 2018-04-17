import {Airport} from "./Airport";
import {Airline} from "./Airline";
import {DynamicEnum} from "./DynamicEnum";
import {flights, Flights} from "./Flights";
import {GeoLocation} from "./GeoLocation";
import {Date} from "./Date";
import {GetArray} from "./GetArray";
import {Time} from "./Time";

interface FlightsModule extends Module {
    
    Flights: {
        
        create(flightsData: Uint8Array, airportsData: Uint8Array, airlinesData: Uint8Array): Flights;
        
        jsCreate(flightsData: Uint8Array, airportsData: Uint8Array, airlinesData: Uint8Array): Flights;
        
    };
    
    Airport: {
        
        count(): number;
        
        numAirports(): number;
        
        of(index: number): Airport;
        
        all(): Airport[];
        
        airports(): Airport[];
        
    };
    
    Airline: {
        
        count(): number;
        
        numAirlines(): number;
        
        of(index: number): Airline;
        
        all(): Airline[];
        
        airlines(): Airline[];
        
    };
    
    GeoLocation: {
        
        of(latitude: number, longitude: number): GeoLocation;
        
    };
    
    Date: {
        
        of(dayOfYear: number): Date;
        
    };
    
    Time: {
        
        of(minuteOfDay: number): Time;
        
    };
    
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
    Module.Flights.create = function(flightsData: Uint8Array, airportsData: Uint8Array,
                                     airlinesData: Uint8Array): Flights {
        console.log("create", arguments);
        return Module.Flights.jsCreate(flightsData, airportsData, airlinesData);
    };
    
    DynamicEnum.addAllFunction(Module.Airport, "airports");
    DynamicEnum.addAllFunction(Module.Airline, "airlines");
    
};

export const extendFlightsInterfaces = function() {
    GetArray.addToArrayFunction(flights);
    GetArray.addToArrayFunction(flights.get(0));
};

export const postWasm = function(): void {
    console.log("postWasm");
    
    extendInterfaces(Module);
    
};