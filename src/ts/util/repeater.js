"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const class_1 = require("./class");
exports.Repeater = class_1.Class.new(() => {
    let _interval = () => 0;
    let _stopCondition = () => false;
    let _callback = () => undefined;
    let _initialDelay = true;
    return Object.freeze({
        interval(interval) {
            let intervalFunc;
            if (typeof interval === "number") {
                const intervalValue = interval;
                intervalFunc = () => intervalValue;
            }
            else {
                intervalFunc = interval;
            }
            _interval = i => intervalFunc(i) * 1000; // use seconds, not ms
            return this;
        },
        until(stopCondition) {
            _stopCondition = stopCondition;
            return this;
        },
        numRepeats(numRepeats) {
            if (numRepeats < 0) {
                numRepeats = 0;
            }
            return this.until(i => i >= numRepeats);
        },
        noInitialDelay(noDelay = true) {
            _initialDelay = !noDelay;
            return this;
        },
        calling(callback) {
            _callback = callback;
            return this;
        },
        start() {
            const interval = _interval;
            const stopCondition = _stopCondition;
            const callback = _callback;
            const initialDelay = _initialDelay;
            const ids = [];
            const promise = new Promise(resolve => (function runOnce(i) {
                const currentInterval = interval(i);
                // console.log("currentInterval: " + currentInterval);
                const id = setTimeout(() => {
                    if (stopCondition(i, currentInterval)) {
                        resolve();
                        return;
                    }
                    callback(i, currentInterval);
                    runOnce(i + 1);
                }, !initialDelay && i === 0 ? 0 : currentInterval);
                ids.push(id);
            })(0));
            promise.cancel = () => ids.forEach(clearTimeout);
            return promise;
        },
    });
});
//# sourceMappingURL=repeater.js.map