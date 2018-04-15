export type Fetch = typeof fetch;

const deserializeResponse = function(serialized: string): Response {
    return new Response(new TextEncoder().encode(serialized));
};

const serializeResponse = function(arrayBuffer: ArrayBuffer): string {
    return new TextDecoder().decode(arrayBuffer);
};

export const cachedFetch: Fetch = function(input: string | Request, init?: RequestInit): Promise<Response> {
    const key: string = JSON.stringify({
        input: input,
        init: init,
    });
    const cachedValue: string | null = localStorage.getItem(key);
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
            } catch (e) {
                console.log("unable to cache in localStorage");
                console.log(e);
            }
            return new Response(buffer);
        });
};