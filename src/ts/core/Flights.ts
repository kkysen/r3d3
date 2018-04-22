import {cachedFetch, Fetch} from "../util/cachedFetch";
import {SHA} from "../util/hash";
import {Airport} from "./Airport";
import {Flight} from "./Flight";
import {FlightsInDay} from "./FlightsInDay";
import {GetArray} from "./GetArray";
import {Module, postWasm, runAfterWasm} from "./wasm";

export interface Flights extends GetArray<FlightsInDay> {
    
    // TODO
    
    numDays(): number;
    
    numFlights(): number;
    
    flight(day: number, i: number): Flight;
    
    // TODO
    forEach(func: (Flight) => void): void;
    
    totalDistance(): number;
    
}

export interface FlightsSingleton {
    
    get(): Promise<Flights>;
    
}

export const flightsPromise: FlightsSingleton = (function() {
    
    const hex = function(buffer: ArrayBuffer): string {
        const hexCodes = [];
        const view = new DataView(buffer);
        for (let i = 0; i < view.byteLength; i += 4) {
            // Using getUint32 reduces the number of iterations needed (we process 4 bytes each time)
            const value = view.getUint32(i);
            // toString(16) will give the hex representation of the number without padding
            const stringValue = value.toString(16);
            // We use concatenation and slice for padding
            const padding = "00000000";
            const paddedValue = (padding + stringValue).slice(-padding.length);
            hexCodes.push(paddedValue);
        }
        
        // Join all the hex strings into one
        return hexCodes.join("");
    };
    
    // let i = 0;
    const asUint8Array = async function(response: Response): Promise<Uint8Array> {
        // console.log(response);
        // const j = ++i;
        const buffer: Uint8Array = new Uint8Array(await response.arrayBuffer());
        // SHA._256.hash(buffer).then(hash => console.log(j, hash));
        return buffer;
    };
    
    const loadFlights = function(_flights: Uint8Array): Flights {
        return flights = (<any> window).flights = Module.Flights.create(_flights);
    };
    
    const fetchData = function <T>(name: string, init: (Uint8Array) => T): Promise<T> {
        return cachedFetch("data/" + name)
            .then(asUint8Array)
            .then(init);
    };
    
    const create = function(): Promise<Flights> {
        // load all data in parallel, but airlines and airports must be processed before flights
        return Promise.all([
            fetchData("airlines.csv", Module.Airline.load),
            fetchData("airports.csv", Module.Airport.load.then(() => {
                Airport.extend();
                postWasm.then(Module.Airport.plotAll);
            })),
            fetchData("flights.bin", data => data),
        ])
            .then(([airlines, airports, flights]) => loadFlights(flights));
    };
    
    let promise;
    return {
        get(): Promise<Flights> {
            return promise || (promise = create());
        }
    };
    
})();

export let flights: Flights;