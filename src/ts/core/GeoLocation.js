"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const map_1 = require("./map");
exports.GeoLocation = {
    extendOn(location) {
        const prototype = Object.getPrototypeOf(location);
        if (prototype.extended) {
            return;
        }
        prototype.extended = true;
        prototype.coordinates = function () {
            return [this.longitude(), this.latitude()];
        };
        const projection = map_1.Map.projection;
        const svg = map_1.Map.svg;
        prototype.scale = function () {
            return projection(this.coordinates());
        };
        prototype.plot = function (radius, color) {
            const point = this.scale();
            return svg.append("circle")
                .attrs({
                cx: point[0],
                cy: point[1],
                r: radius,
                fill: color,
            });
        };
    },
};
//# sourceMappingURL=GeoLocation.js.map