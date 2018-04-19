import {Range} from "../util/range";

export interface DynamicEnum<T> {
    
    load(data: Uint8Array): void;
    
    count(): number;
    
    of(index: number): T;
    
    all(): T[];
    
    flush(): void;
    
}

export const DynamicEnum = {
    
    extendOn<T>(dynamicEnum: DynamicEnum<T>, alias?: string) {
        const cache = dynamicEnum as any as {_all: T[]};
        
        dynamicEnum.all = function(): T[] {
            if (!cache._all) {
                cache._all = Range.new(dynamicEnum.count())
                    .map(i => dynamicEnum.of(i));
            }
            return cache._all;
        };
        
        if (alias) {
            dynamicEnum[alias] = dynamicEnum.all;
        }
        
        dynamicEnum.flush = function(): void {
            cache._all = undefined;
        };
        
    },
    
};