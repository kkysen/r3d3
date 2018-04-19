import {Range} from "../util/range";

export interface GetArray<T> {

    size(): number;
    
    get(i: number): T;
    
    toArray(): T[];
    
    flush(): void;

}

export const GetArray = {
    
    extendOn<T>(getArray: GetArray<T>): void {
        const prototype = Object.getPrototypeOf(getArray);
        if (prototype.getArrayExtended) {
            return;
        }
        prototype.getArrayExtended = true;
        
        prototype.toArray = function(this: GetArray<T>): T[] {
            const cache = this as any as {_array: T[]};
            if (!cache._array) {
                cache._array = Range.new(this.size())
                    .map(i => this.get(i));
            }
            return cache._array;
        };
        
        prototype.flush = function(this: GetArray<T>): void {
            (this as any as {_array: T[]})._array = undefined;
        };
        
    },
    
};