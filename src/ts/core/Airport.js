"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Airport = {
    extendOn(airport) {
        const prototype = Object.getPrototypeOf(location);
        if (prototype.extended) {
            return;
        }
        prototype.extended = true;
        prototype.plot = function () {
            const circle = this.location().plot(5, "green");
            circle.on("mouseover", () => {
                circle.append("title").text(this.iataCode + ": " + this.name());
            });
            return circle;
        };
    },
};
//# sourceMappingURL=Airport.js.map