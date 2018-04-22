"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const wasm_1 = require("./wasm");
const extendOn = function (airport) {
    const prototype = Object.getPrototypeOf(airport);
    if (prototype.extended) {
        return;
    }
    prototype.extended = true;
    prototype.plot = function () {
        const circle = this.location().plot(5, "blue");
        return circle && circle.on("mouseover", () => {
            circle.append("title").text(this.iataCode() + ": " + this.name());
        });
    };
};
exports.Airport = {
    extend() {
        wasm_1.Module.Airport.plotAll = function () {
            return wasm_1.Module.Airport.all()
                .map(airport => airport.plot())
                .filter(e => e !== null);
        };
        extendOn(wasm_1.Module.Airport.of(0));
    },
};
//# sourceMappingURL=Airport.js.map