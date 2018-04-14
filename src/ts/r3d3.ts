import {flights} from "./core/Flights";

export const main = function() {
    console.log(main);
    flights.get()
        .then(flights => {
            console.log(flights);
        });
};