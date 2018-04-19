"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const range_1 = require("../util/range");
exports.DynamicEnum = {
    extendOn(dynamicEnum, alias) {
        const cache = dynamicEnum;
        dynamicEnum.all = function () {
            if (!cache._all) {
                cache._all = range_1.Range.new(dynamicEnum.count())
                    .map(i => dynamicEnum.of(i));
            }
            return cache._all;
        };
        if (alias) {
            dynamicEnum[alias] = dynamicEnum.all;
        }
        dynamicEnum.flush = function () {
            cache._all = undefined;
        };
    },
};
//# sourceMappingURL=DynamicEnum.js.map