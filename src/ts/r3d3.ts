import {flier, renderFlights} from "./core/FlightRenderer";
import {flights, flightsPromise} from "./core/Flights";
import {createMap} from "./core/Map";
import {extendFlightsInterfaces, postWasm, runAfterWasm, Module} from "./core/wasm";
import d3 = require("d3");

const timeDistances = (<any> window).timeDistances = function(): void {
    console.log("running");
    // let distance: number = 0;
    // for (let i = 0; i < flights.size(); i++) {
    //     console.log(i, distance);
    //     const flightsInDay = flights.get(i);
    //     for (let j = 0; j < flightsInDay.size(); j++) {
    //         distance += flightsInDay.get(j).distance();
    //     }
    // }
    console.log(flights.totalDistance());
};

const flightsMain = function(): void {
    // const flightsInDay = flightsPromise.flightsInDay(1);
    // console.log(flightsInDay);
    const flight = flights.flight(0, 0);
    console.log(flight);
    console.log(flight.departure());
    console.log(flight.departure().airport());
    console.log(flight.departure().airport().name());
    
    timeDistances.timed()();
    
    (<any> window).flight = flights.flight(0, 0);
};

const preFlightsMain = function(): void {
    createMap();
    flier();
};

const realMain = function(): void {
    console.log("realMain");
    preFlightsMain();
    flightsPromise.get()
        .then(flights => {
            console.log(flights);
            // global flights will have loaded now
            extendFlightsInterfaces();
            flightsMain();
        });
};

export const main = function(): void {
    (<any> window).d3 = d3;
    postWasm.then(realMain);
};
