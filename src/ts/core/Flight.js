"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const range_1 = require("../util/range");
exports.Flight = {
    extendOn(flight) {
        const prototype = Object.getPrototypeOf(location);
        if (prototype.extended) {
            return;
        }
        prototype.extended = true;
        const RED = [255, 0, 0];
        const GREEN = [0, 255, 0];
        const mixColors = function (color1, color2, weight) {
            if (weight < 0) {
                weight = 0;
            }
            if (weight > 1) {
                weight = 1;
            }
            const weight1 = weight;
            const weight2 = 1 - weight;
            return "rgb("
                + range_1.Range.new(3).map(i => Math.round(color1[i] * weight1 + color2[i] * weight2))
                    .join(",")
                + ")";
        };
        prototype.render = function () {
            const departure = this.departure();
            const arrival = this.arrival();
            const startDelay = departure.delay().minuteOfDay();
            const endDelay = arrival.delay().minuteOfDay();
            const duration = this.duration().minuteOfDay();
            const start = departure.airport().location();
            const end = arrival.airport().location();
            const endPoint = end.scale();
            const startColor = mixColors(RED, GREEN, startDelay / 30);
            const endColor = mixColors(RED, GREEN, endDelay / 30);
            console.log({
                departure: departure,
                arrival: arrival,
                duration: duration,
                start: start,
                end: end,
                startDelay: startDelay,
                endDelay: endDelay,
                startColor: startColor,
                endColor: endColor,
            });
            start.plot(5)
                .attrs({ fill: startColor })
                .transition()
                .duration(duration)
                .attrs({
                cx: endPoint[0],
                cy: endPoint[1],
                fill: endColor,
            });
        };
    },
};
//# sourceMappingURL=Flight.js.map