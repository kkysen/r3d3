type Runnable = () => void;

interface Module {
    
    // preamble.js
    
    readonly wasmMemory: WebAssembly.Memory;
    
    readonly HEAP: ArrayBuffer;
    
    readonly HEAP8: Int8Array;
    readonly HEAP16: Int16Array;
    readonly HEAP32: Int32Array;
    
    readonly HEAPU8: Uint8Array;
    readonly HEAPU16: Uint16Array;
    readonly HEAPU32: Uint32Array;
    
    readonly HEAPF32: Float32Array;
    readonly HEAPF64: Float64Array;
    
    readonly STACKTOP: number;
    
    ccall(ident: string, returnType: string, argTypes: string[], args: any[]): any;
    
    cwrap(ident: string, returnType: string, argTypes: string[]): (...args: any[]) => any;
    
    getValue(ptr: number, type: string): number;
    
    getValue(ptr: number, type: string, noSafe: boolean): number;
    
    setValue(ptr: number, value: number, type: string): void;
    
    setValue(ptr: number, value: number, type: string, noSafe: boolean): void;
    
    Pointer_stringify(ptr: number): string;
    
    Pointer_stringify(ptr: number, length: number): string;
    
    lengthBytesUTF16(str: string): number;
    
    UTF8ToString(ptr: number): string;
    
    stringToUTF8(str: string, outPtr: number, maxBytes: number): void;
    
    lengthBytesUTF32(str: string): number;
    
    UTF16ToString(ptr: number): string;
    
    stringToUTF16(str: number, outPtr: number, maxBytes: number): void;
    
    lengthBytesUTF8(str: string): number;
    
    UTF32ToString(ptr: number): string;
    
    stringToUTF32(str: number, outPtr: number, maxBytes: number): void;
    
    intArrayFromString(str: string, dontAddNull: boolean): number[];
    
    intArrayFromString(str: string, dontAddNull: boolean, length: number): number[];
    
    intArrayToString(array: number[]): string;
    
    writeArrayToMemory<T>(array: T[], buffer: number): void;
    
    writeAsciiToMemory(str: string, buffer: number, dontAddNull: boolean): void;
    
    addRunDependency(id: string): void;
    
    removeRunDependency(id: string): void;
    
    addFunction(func: (...args: any[]) => any, signature: string): number;
    
    removeFunction(funcPtr: number): void;
    
    stackTrace(): void; // TODO FIXME
    
    readonly preRun: Runnable[];
    
    readonly postRun: Runnable[];
    
}

declare var Module: Module;