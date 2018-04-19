"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const Flights_1 = require("./Flights");
exports.renderFlights = function () {
    for (let day = 0; day < Flights_1.flights.numDays(); day++) {
        const flightsInDay = Flights_1.flights.get(day);
        for (let i = 0; i < flightsInDay.numFlights(); i++) {
            const flight = flightsInDay.get(i);
            flight.render();
        }
    }
};
window.renderFlights = exports.renderFlights;
//# sourceMappingURL=FlightRenderer.js.map