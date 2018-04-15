import {Flights} from "./Flights";

declare interface FlightsModule extends Module {
    
    Flights: {
        
        create(flightsData: Uint8Array, airportsData: Uint8Array, airlinesData: Uint8Array): Flights;
        
        jsCreate(flightsData: Uint8Array, flightsDataLength: number,
                 airportsData: Uint8Array, airportsDataLength: number,
                 airlinesData: Uint8Array, airlinesDataLength: number): Flights;
        
    };
    
}

Module.Flights.create = function(flightsData: Uint8Array, airportsData: Uint8Array, airlinesData: Uint8Array): Flights {
    return Module.Flights.jsCreate(
        flightsData, flightsData.length,
        airportsData, airportsData.length,
        airlinesData, airlinesData.length
    );
};

export declare var Module: FlightsModule;