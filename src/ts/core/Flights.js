"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const cachedFetch_1 = require("../util/cachedFetch");
const Airport_1 = require("./Airport");
const wasm_1 = require("./wasm");
exports.flightsPromise = (function () {
    const hex = function (buffer) {
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
    const asUint8Array = async function (response) {
        // console.log(response);
        // const j = ++i;
        const buffer = new Uint8Array(await response.arrayBuffer());
        // SHA._256.hash(buffer).then(hash => console.log(j, hash));
        return buffer;
    };
    const loadFlights = function (_flights) {
        return exports.flights = window.flights = wasm_1.Module.Flights.create(_flights);
    };
    const fetchData = function (name, init) {
        return cachedFetch_1.cachedFetch("data/" + name)
            .then(asUint8Array)
            .then(init);
    };
    const create = function () {
        // load all data in parallel, but airlines and airports must be processed before flights
        return Promise.all([
            fetchData("airlines.csv", wasm_1.Module.Airline.load),
            fetchData("airports.csv", wasm_1.Module.Airport.load.then(() => {
                Airport_1.Airport.extend();
                wasm_1.postWasm.then(wasm_1.Module.Airport.plotAll);
            })),
            fetchData("flights.bin", data => data),
        ])
            .then(([airlines, airports, flights]) => loadFlights(flights));
    };
    let promise;
    return {
        get() {
            return promise || (promise = create());
        }
    };
})();
//# sourceMappingURL=Flights.js.map