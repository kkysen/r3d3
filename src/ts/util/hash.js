"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const makeSha = function (numBits) {
    const toBuffer = function (data) {
        if (Object.prototype.toString.call(data) === "[object String]") {
            return new TextEncoder().encode(data);
        }
        return data;
    };
    return {
        async hash(data) {
            const buffer = toBuffer(data);
            const hashBuffer = await crypto.subtle.digest("SHA-" + numBits, buffer);
            const hashArray = Array.from(new Uint8Array(hashBuffer));
            return hashArray.map(b => ("00" + b.toString(16)).slice(-2)).join("");
        },
    }.freeze();
};
exports.SHA = [1, 256, 384, 512]
    .reduce((obj, numBits) => (Object.assign({}, obj, { ["_" + numBits]: makeSha(numBits) })), {})
    .freeze();
//# sourceMappingURL=hash.js.map