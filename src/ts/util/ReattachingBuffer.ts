export type AnyFunction = (...args: any[]) => any;

export type Reattacher = () => void;

export type Detacher = AnyFunction & {
    
    detacher: AnyFunction;
    
    attached: Reattacher[];
    
}

export interface ReattachingBuffer<T> {
    
    detacher: Detacher;
    
    get(): T;
    
}

export const ReattachingBuffer = {
    
    new<T, DetacherParent, DetacherName extends keyof DetacherParent>(
        supplier: () => T, detacherParent: DetacherParent, detacherName: DetacherName): ReattachingBuffer<T> {
        let detacher: Detacher = <Detacher> <any> detacherParent[detacherName];
        if (!detacher.detacher) {
            const realDetacher: AnyFunction = detacher;
            detacher = <Detacher> function(...args: any[]): any {
                realDetacher.call(this, args);
                for (const reattacher of detacher.attached) {
                    reattacher();
                }
            };
            detacher.attached = [];
            detacher.detacher = realDetacher;
            detacherParent[detacherName] = <DetacherParent[DetacherName]> <any> detacher;
        }
        
        let value = supplier();
        detacher.attached.push(() => {
            value = supplier();
        });
        
        return {
            
            detacher: detacher,
            
            get(): T {
                return value;
            },
            
        };
    },
    
    onWasmMemoryGrowth<T>(supplier: () => T): ReattachingBuffer<T> {
        return ReattachingBuffer.new(supplier, Module.wasmMemory, "grow");
    },
    
};