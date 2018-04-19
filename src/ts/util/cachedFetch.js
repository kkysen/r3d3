"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const deserializeResponse = function (serialized) {
    return new Response(new TextEncoder().encode(serialized));
};
const serializeResponse = function (arrayBuffer) {
    return new TextDecoder().decode(arrayBuffer);
};
exports.cachedSimpleFetch = function (input, init) {
    const key = JSON.stringify({
        input: input,
        init: init,
    });
    const cachedValue = localStorage.getItem(key);
    if (cachedValue) {
        return Promise.resolve(deserializeResponse(cachedValue));
    }
    init = init || {};
    init.cache = "reload"; // force reload, b/c caching anyways
    return fetch(input, init)
        .then(response => response.arrayBuffer())
        .then(buffer => {
        try {
            localStorage.setItem(key, serializeResponse(buffer));
        }
        catch (e) {
            console.log("unable to cache in localStorage");
            console.log(e);
        }
        return new Response(buffer);
    });
};
const makeFetchAs = function (then) {
    return (input, init) => exports.cachedSimpleFetch(input, init).then(then);
};
exports.cachedFetch = Object.assign(exports.cachedSimpleFetch, ...[
    response => response.text(),
    response => response.json(),
    response => response.arrayBuffer(),
    response => response.blob(),
].map(makeFetchAs));
//# sourceMappingURL=cachedFetch.js.map