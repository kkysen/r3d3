"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const deserializeResponse = function (serialized) {
    return new Response(new TextEncoder().encode(serialized));
};
const serializeResponse = function (arrayBuffer) {
    return new TextDecoder().decode(arrayBuffer);
};
const serializeFetchArgs = function (args) {
    return JSON.stringify(args);
};
const onLoadFuncs = {};
const onLoad = function (url) {
    let args;
    if (!url.input) {
        args = { input: url };
    }
    else {
        args = url;
    }
    const key = serializeFetchArgs(args);
    if (!(key in onLoadFuncs)) {
        onLoadFuncs[key] = [];
    }
    return new Promise(resolve => {
        onLoadFuncs[key].push(resolve);
    });
};
const baseCachedFetch = function (input, init) {
    const key = serializeFetchArgs({
        input: input,
        init: init,
    });
    const cachedValue = localStorage.getItem(key);
    if (cachedValue) {
        return [key, Promise.resolve(deserializeResponse(cachedValue))];
    }
    init = init || {};
    init.cache = "reload"; // force reload, b/c caching anyways
    return [
        key, fetch(input, init)
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
        })
    ];
};
exports.cachedSimpleFetch = function (input, init) {
    const [key, promise] = baseCachedFetch(input, init);
    return promise.then(response => {
        if (onLoadFuncs[key]) {
            for (const onLoad of onLoadFuncs[key]) {
                onLoad();
            }
        }
        return response;
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
exports.cachedFetch.onLoad = onLoad;
//# sourceMappingURL=cachedFetch.js.map