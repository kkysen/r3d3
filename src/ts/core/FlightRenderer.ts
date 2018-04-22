import {Flight} from "./Flight";
import {flights} from "./Flights";
import {FlightsInDay} from "./FlightsInDay";


export const renderFlights = function() {
    for (let day = 0; day < flights.numDays(); day++) {
        const flightsInDay: FlightsInDay = flights.get(day);
        for (let i = 0; i < flightsInDay.numFlights(); i++) {
            const flight: Flight = flightsInDay.get(i);
            flight.wasmRender();
        }
    }
};

(<any> window).renderFlights = renderFlights;