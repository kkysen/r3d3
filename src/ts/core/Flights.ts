import {cachedFetch, Fetch} from "../util/cachedFetch";
import {SHA} from "../util/hash";
import {Flight} from "./Flight";
import {FlightsInDay} from "./FlightsInDay";
import {GetArray} from "./GetArray";
import {Module} from "./wasm";

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
    
    let i = 0;
    const asUint8Array = async function(response: Response): Promise<Uint8Array> {
        console.log(response);
        const j = ++i;
        const buffer: Uint8Array = new Uint8Array(await response.arrayBuffer());
        // SHA._256.hash(buffer).then(hash => console.log(j, hash));
        return buffer;
    };
    
    const loadFlights = function(_flights: Uint8Array, airports: Uint8Array, airlines: Uint8Array): Flights {
        return flights = (<any> window).flights = Module.Flights.create(_flights, airports, airlines);
    };
    
    const create = function(): Promise<Flights> {
        Promise.all = Promise.all.bind(Promise);
        return ["flights.bin", "airports.csv", "airlines.csv"]
            .map(name => "data/" + name)
            .map(url => cachedFetch(url))
            .applyOn(Promise.all)
            .then(asUint8Array.mapping())
            .then(Promise.all)
            .then(loadFlights.applying());
    };
    
    let promise;
    return {
        get(): Promise<Flights> {
            return promise || (promise = create());
        }
    };
    
})();

export let flights: Flights;