"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const cachedFetch_1 = require("../util/cachedFetch");
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
    const loadFlights = function (_flights, airports, airlines) {
        return exports.flights = window.flights = wasm_1.Module.Flights.create(_flights, airports, airlines);
    };
    const create = function () {
        Promise.all = Promise.all.bind(Promise);
        return ["flights.bin", "airports.csv", "airlines.csv"]
            .map(name => "data/" + name)
            .map(url => cachedFetch_1.cachedFetch(url))
            .applyOn(Promise.all)
            .then(asUint8Array.mapping())
            .then(Promise.all)
            .then(loadFlights.applying());
    };
    let promise;
    return {
        get() {
            return promise || (promise = create());
        }
    };
})();
//# sourceMappingURL=Flights.js.map