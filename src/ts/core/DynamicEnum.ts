import {Range} from "../util/range";

interface DynamicEnum<T> {
    
    count(): number;
    
    of(index: number): T;
    
    all(): T[];
    
}

export const DynamicEnum = {
    
    addAllFunction<T>(dynamicEnum: DynamicEnum<T>, alias?: string) {
        dynamicEnum.all = function(): T[] {
            return Range.new(dynamicEnum.count())
                .map(i => dynamicEnum.of(i));
        };
        if (alias) {
            dynamicEnum[alias] = dynamicEnum.all;
        }
    },
    
};