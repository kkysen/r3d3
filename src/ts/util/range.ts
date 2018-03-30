export interface Range {
    
    map<T>(func: (i: number) => T): T[];
    
    forEach(func: (i: number) => void): void;
    
    toArray(): number[];
    
    toInterval(): number[];
    
}

export type RangeClass = {
    
    new: (from: number, to?: number) => Range;
    
    ofDomain(domain: number[]): Range;
    
};

export const Range: RangeClass = Object.freeze({
    
    new(from: number, to?: number): Range {
        if (!to) {
            to = from;
            from = 0;
        }
        
        return {
            
            map<T>(func: (i: number) => T): T[] {
                const a: T[] = new Array(to - from);
                for (let i: number = from; i < to; i++) {
                    a[i - from] = func(i);
                }
                return a;
            },
            
            forEach(func: (i: number) => void): void {
                for (let i: number = from; i < to; i++) {
                    func(i);
                }
            },
    
            toArray(): number[] {
                return this.map(i => i);
            },
            
            toInterval(): number[] {
                return [from, to];
            },
            
        };
        
    },
    
    ofDomain(domain: number[]): Range {
        return this.new(Math.min(...domain), Math.max(...domain));
    },
    
});