"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const Flights_1 = require("./core/Flights");
exports.main = function () {
    Flights_1.flights.get()
        .then(flights => {
        console.log(flights);
    });
};
//# sourceMappingURL=r3d3.js.map