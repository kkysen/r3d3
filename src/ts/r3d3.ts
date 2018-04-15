import {flights} from "./core/Flights";
import {postWasm, runAfterWasm} from "./core/wasm";

const realMain = function() {
    console.log("realMain");
    flights.get()
        .then(flights => {
            console.log(flights);
            // const flightsInDay = flights.flightsInDay(1);
            // console.log(flightsInDay);
            const flight = flights.flightInDay(0, 0);
            console.log(flight);
            console.log(flight.departure());
            console.log(flight.departure().airport());
            console.log(flight.departure().airport().name());
            
            let distance: number = 0;
            for (let i = 0; i < 100; i++) {
                distance += flights.flightInDay(0, i).distance();
            }
            console.log(distance);
        });
};

export const main = function() {
    [postWasm, realMain].forEach(runAfterWasm);
};