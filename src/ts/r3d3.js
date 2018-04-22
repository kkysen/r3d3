"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const FlightRenderer_1 = require("./core/FlightRenderer");
const Flights_1 = require("./core/Flights");
const map_1 = require("./core/map");
const wasm_1 = require("./core/wasm");
const d3 = require("d3");
const timeDistances = window.timeDistances = function () {
    console.log("running");
    // let distance: number = 0;
    // for (let i = 0; i < flights.size(); i++) {
    //     console.log(i, distance);
    //     const flightsInDay = flights.get(i);
    //     for (let j = 0; j < flightsInDay.size(); j++) {
    //         distance += flightsInDay.get(j).distance();
    //     }
    // }
    console.log(Flights_1.flights.totalDistance());
};
const flightsMain = function () {
    // const flightsInDay = flightsPromise.flightsInDay(1);
    // console.log(flightsInDay);
    const flight = Flights_1.flights.flight(0, 0);
    console.log(flight);
    console.log(flight.departure());
    console.log(flight.departure().airport());
    console.log(flight.departure().airport().name());
    timeDistances.timed()();
    console.log(FlightRenderer_1.renderFlights);
    window.flight = Flights_1.flights.flight(0, 0);
};
const preFlightsMain = function () {
    map_1.createMap();
};
const realMain = function () {
    console.log("realMain");
    preFlightsMain();
    Flights_1.flightsPromise.get()
        .then(flights => {
        console.log(flights);
        // global flights will have loaded now
        wasm_1.extendFlightsInterfaces();
        flightsMain();
    });
};
exports.main = function () {
    window.d3 = d3;
    wasm_1.postWasm.then(realMain);
};
//# sourceMappingURL=r3d3.js.map