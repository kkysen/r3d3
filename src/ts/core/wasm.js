"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const Airport_1 = require("./Airport");
const DynamicEnum_1 = require("./DynamicEnum");
const Flights_1 = require("./Flights");
const GeoLocation_1 = require("./GeoLocation");
const GetArray_1 = require("./GetArray");
const map_1 = require("./map");
exports.Module = undefined;
exports.runAfterWasm = function (func) {
    // console.log(func);
    exports.Module = exports.Module || window.Module;
    return new Promise(resolve => {
        const wrapper = function () {
            resolve(func());
        };
        if (exports.Module.Flights) {
            wrapper();
        }
        else {
            exports.Module.postRun.push(wrapper);
        }
    });
};
const extendInterfaces = function (Module) {
    Module.Flights.create = function (flightsData, airportsData, airlinesData) {
        // console.log("create", arguments);
        return Module.Flights.jsCreate(flightsData, airportsData, airlinesData);
    };
    DynamicEnum_1.DynamicEnum.extendOn(Module.Airport, "airports");
    DynamicEnum_1.DynamicEnum.extendOn(Module.Airline, "airlines");
    Module.Map = map_1.Map;
    GeoLocation_1.GeoLocation.extendOn(Module.GeoLocation.of(0, 0));
    Airport_1.Airport.extendOn(Module.Airport.of(0));
};
exports.extendFlightsInterfaces = function () {
    GetArray_1.GetArray.extendOn(Flights_1.flights);
    GetArray_1.GetArray.extendOn(Flights_1.flights.get(0));
};
exports.postWasm = function () {
    console.log("postWasm");
    extendInterfaces(exports.Module);
};
//# sourceMappingURL=wasm.js.map