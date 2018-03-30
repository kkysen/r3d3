export const Class = Object.freeze({
    
    new<T>(constructor: (...args: any[]) => T, freeze = true) {
        const klass = {
            new: constructor
        };
        if (freeze) {
            Object.freeze(klass);
        }
        return klass;
    },
    
});