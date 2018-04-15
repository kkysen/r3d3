"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const Flights_1 = require("./core/Flights");
const wasm_1 = require("./core/wasm");
const realMain = function () {
    Flights_1.flights.get()
        .then(flights => {
        console.log(flights);
    });
};
exports.runAfterWasm = function (func) {
    console.log(func);
    return new Promise(resolve => {
        const wrapper = function () {
            resolve(func());
        };
        if (wasm_1.Module.Flights) {
            wrapper();
        }
        else {
            wasm_1.Module.postRun.push(wrapper);
        }
    });
};
exports.main = function () {
    // noinspection JSIgnoredPromiseFromCall
    exports.runAfterWasm(realMain);
};
//# sourceMappingURL=r3d3.js.map