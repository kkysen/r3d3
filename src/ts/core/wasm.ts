import {Flights} from "./Flights";

interface FlightsModule extends Module {
    
    Flights: {
        
        create(flightsData: Uint8Array, airportsData: Uint8Array, airlinesData: Uint8Array): Flights;
        
        jsCreate(flightsData: Uint8Array, airportsData: Uint8Array, airlinesData: Uint8Array): Flights;
        
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

export const postWasm = function(): void {
    console.log("postWasm");
    Module.Flights.create = function(flightsData: Uint8Array, airportsData: Uint8Array,
                                     airlinesData: Uint8Array): Flights {
        console.log("create", arguments);
        return Module.Flights.jsCreate(flightsData, airportsData, airlinesData);
    };
};