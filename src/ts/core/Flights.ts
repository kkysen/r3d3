export interface Flights {
    
    // TODO
    
    forEach(func: (Flight) => void): void;
    
}

export interface FlightsSingleton {
    
    get(): Promise<Flights>;
    
}

export const flights: FlightsSingleton = (function() {
    
    const asUint8Array = function(response: Response): Promise<Uint8Array> {
        return response.arrayBuffer()
            .then(buffer => new Uint8Array(buffer));
    };
    
    const loadFlights = function(flights: Uint8Array, airports: Uint8Array, airlines: Uint8Array): Flights {
        // TODO FIXME
        const Module: any = {}; // TODO temp so no errors
        return Module.Flights.create(
            flights.buffer, flights.byteLength,
            airports.buffer, airports.byteLength,
            airlines.buffer, airlines.byteLength,
        );
    };
    
    const baseUrl = "/data/";
    
    const create = function(): Promise<Flights> {
        return new Promise(resolve => {
            fetch(baseUrl + "airlines")
                .then(asUint8Array)
                .then(airlines => {
                    fetch(baseUrl + "airports")
                        .then(asUint8Array)
                        .then(airports => {
                            fetch(baseUrl + "flights")
                                .then(asUint8Array)
                                .then(flights => {
                                    resolve(loadFlights(flights, airports, airlines));
                                });
                        });
                });
        });
    };
    
    let promise;
    return {
        get(): Promise<Flights> {
            return promise || (promise = create());
        }
    };
    
})();