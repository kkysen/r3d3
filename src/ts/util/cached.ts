export interface Cached<T> {
    
    get(): Promise<T>,
    
    value?: Promise<T>;
    
}

export const Cached = {
    new<T>(getter: () => Promise<T>): Cached<T> {
        const cache: Cached<T> = {
            value: undefined,
            get(): Promise<T> {
                if (cache.value === undefined) {
                    cache.value = getter();
                }
                return Promise.resolve(cache.value);
            },
        };
        return cache.freeze();
    },
};