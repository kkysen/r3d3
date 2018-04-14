"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.flights = (function () {
    const asUint8Array = function (response) {
        return response.arrayBuffer()
            .then(buffer => new Uint8Array(buffer));
    };
    const loadFlights = function (flights, airports, airlines) {
        // TODO FIXME
        const Module = {}; // TODO temp so no errors
        return Module.Flights.create(flights.buffer, flights.byteLength, airports.buffer, airports.byteLength, airlines.buffer, airlines.byteLength);
    };
    const baseUrl = "/data/";
    const create = function () {
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
        get() {
            return promise || (promise = create());
        }
    };
})();
//# sourceMappingURL=Flights.js.map