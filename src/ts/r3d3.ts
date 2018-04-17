import {flights, flightsPromise} from "./core/Flights";
import {extendFlightsInterfaces, postWasm, runAfterWasm} from "./core/wasm";
import {cachedFetch} from "./util/cachedFetch";
import d3 = require("d3");

const timeDistances = (<any> window).timeDistances = function() {
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

const flightsMain = function() {
    // const flightsInDay = flightsPromise.flightsInDay(1);
    // console.log(flightsInDay);
    const flight = flights.flight(0, 0);
    console.log(flight);
    console.log(flight.departure());
    console.log(flight.departure().airport());
    console.log(flight.departure().airport().name());
    
    timeDistances.timed()();
};

const preFlightsMain = function() {
    (<any> window).d3 = d3;
    
    const div = document.body.appendDiv();
    
    cachedFetch("map.svg")
        .then(response => response.text())
        .then(svg => {
            div.innerHTML = svg;
        })
};

const realMain = function() {
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

export const main = function() {
    [postWasm, realMain].forEach(runAfterWasm);
};