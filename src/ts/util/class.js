"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Class = Object.freeze({
    new(constructor, freeze = true) {
        const klass = {
            new: constructor
        };
        if (freeze) {
            Object.freeze(klass);
        }
        return klass;
    },
});
//# sourceMappingURL=class.js.map