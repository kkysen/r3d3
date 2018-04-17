import {Range} from "../util/range";

export interface GetArray<T> {

    size(): number;
    
    get(i: number): T;
    
    toArray(): T[];

}

export const GetArray = {
    
    addToArrayFunction<T>(getArray: GetArray<T>): void {
        const prototype = Object.getPrototypeOf(getArray);
        if (prototype.toArray) {
            return;
        }
        prototype.toArray = function(this: GetArray<T>): T[] {
            return Range.new(this.size())
                .map(i => this.get(i));
        };
    },
    
};