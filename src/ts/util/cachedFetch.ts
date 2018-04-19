export type Fetch = typeof fetch;

export interface FetchAs<T> {
    
    (input: string | Request, init?: RequestInit): Promise<T>;
    
}

export interface SuperFetch extends Fetch {
    
    text: FetchAs<string>;
    
    json: FetchAs<any>;
    
    arrayBuffer: FetchAs<ArrayBuffer>;
    
    blob: FetchAs<Blob>;
    
    onLoad(url: string | FetchArgs): Promise<void>;
    
}

const deserializeResponse = function(serialized: string): Response {
    return new Response(new TextEncoder().encode(serialized));
};

const serializeResponse = function(arrayBuffer: ArrayBuffer): string {
    return new TextDecoder().decode(arrayBuffer);
};

type FetchArgs = {input: string | Request, init?: RequestInit};

const serializeFetchArgs = function(args: FetchArgs): string {
    return JSON.stringify(args);
};

const onLoadFuncs: {[url: string]: (() => void)[]} = {};

const onLoad = function(url: string | FetchArgs,): Promise<void> {
    let args: FetchArgs;
    if (!(<any> url).input) {
        args = {input: <string> url};
    } else {
        args = <FetchArgs> url;
    }
    const key: string = serializeFetchArgs(args);
    if (!(key in onLoadFuncs)) {
        onLoadFuncs[key] = [];
    }
    return new Promise(resolve => {
        onLoadFuncs[key].push(resolve);
    });
};

const baseCachedFetch = function(input: string | Request, init?: RequestInit): [string, Promise<Response>] {
    const key: string = serializeFetchArgs({
        input: input,
        init: init,
    });
    const cachedValue: string | null = localStorage.getItem(key);
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
                } catch (e) {
                    console.log("unable to cache in localStorage");
                    console.log(e);
                }
                return new Response(buffer);
            })
    ];
};

export const cachedSimpleFetch: Fetch = function(input: string | Request, init?: RequestInit): Promise<Response> {
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

const makeFetchAs = function <T>(then: (Response) => T): FetchAs<T> {
    return (input: string | Request, init?: RequestInit) =>
        cachedSimpleFetch(input, init).then(then);
};

export const cachedFetch: SuperFetch = Object.assign(cachedSimpleFetch, ...[
    response => response.text(),
    response => response.json(),
    response => response.arrayBuffer(),
    response => response.blob(),
].map(makeFetchAs));

cachedFetch.onLoad = onLoad;