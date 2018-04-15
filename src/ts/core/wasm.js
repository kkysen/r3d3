"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const r3d3_1 = require("../r3d3");
// noinspection JSIgnoredPromiseFromCall
r3d3_1.runAfterWasm(() => {
    exports.Module.Flights.create = function (flightsData, airportsData, airlinesData) {
        return exports.Module.Flights.jsCreate(flightsData, flightsData.length, airportsData, airportsData.length, airlinesData, airlinesData.length);
    };
});
//# sourceMappingURL=wasm.js.map