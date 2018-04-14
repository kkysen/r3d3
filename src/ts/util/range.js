"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.Range = Object.freeze({
    new(from, to) {
        if (!to) {
            to = from;
            from = 0;
        }
        return {
            map(func) {
                const a = new Array(to - from);
                for (let i = from; i < to; i++) {
                    a[i - from] = func(i);
                }
                return a;
            },
            forEach(func) {
                for (let i = from; i < to; i++) {
                    func(i);
                }
            },
            toArray() {
                return this.map(i => i);
            },
            toInterval() {
                return [from, to];
            },
        };
    },
    ofDomain(domain) {
        return this.new(Math.min(...domain), Math.max(...domain));
    },
});
//# sourceMappingURL=range.js.map