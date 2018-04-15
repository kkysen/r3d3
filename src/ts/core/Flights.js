"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const wasm_1 = require("./wasm");
exports.flights = (function () {
    const asUint8Array = function (response) {
        return response.arrayBuffer()
            .then(buffer => new Uint8Array(buffer));
    };
    const loadFlights = function (flights, airports, airlines) {
        return wasm_1.Module.Flights.create(flights, airports, airlines);
    };
    const baseUrl = "/data/";
    const create = function () {
        return new Promise(resolve => {
            fetch(baseUrl + "airlines.csv")
                .catch(console.log)
                .then(asUint8Array)
                .then(airlines => {
                fetch(baseUrl + "airports.csv")
                    .catch(console.log)
                    .then(asUint8Array)
                    .then(airports => {
                    fetch(baseUrl + "flights.bin")
                        .catch(console.log)
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