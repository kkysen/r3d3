"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const range_1 = require("../util/range");
exports.GetArray = {
    extendOn(getArray) {
        const prototype = Object.getPrototypeOf(getArray);
        if (prototype.getArrayExtended) {
            return;
        }
        prototype.getArrayExtended = true;
        prototype.toArray = function () {
            const cache = this;
            if (!cache._array) {
                cache._array = range_1.Range.new(this.size())
                    .map(i => this.get(i));
            }
            return cache._array;
        };
        prototype.flush = function () {
            this._array = undefined;
        };
    },
};
//# sourceMappingURL=GetArray.js.map