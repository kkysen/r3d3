"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Cached = {
    new(getter) {
        const cache = {
            value: undefined,
            get() {
                if (cache.value === undefined) {
                    cache.value = getter();
                }
                return Promise.resolve(cache.value);
            },
        };
        return cache.freeze();
    },
};
//# sourceMappingURL=cached.js.map