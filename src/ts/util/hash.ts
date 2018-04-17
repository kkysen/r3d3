export type TypedArray =
    Int8Array
    | Uint8Array
    | Int16Array
    | Uint16Array
    | Int32Array
    | Uint32Array
    | Uint8ClampedArray
    | Float32Array
    | Float64Array;
export type Buffer = TypedArray | ArrayBuffer | DataView;

const makeSha = function(numBits: number): Hash {
    const toBuffer = function(data: string | Buffer): Buffer {
        if (Object.prototype.toString.call(data) === "[object String]") {
            return new TextEncoder().encode(<string> data);
        }
        return <Buffer> data;
    };
    return {
        async hash(data: string | Buffer): Promise<string> {
            const buffer: Buffer = toBuffer(data);
            const hashBuffer: ArrayBuffer = await crypto.subtle.digest("SHA-" + numBits, buffer);
            const hashArray: number[] = Array.from(new Uint8Array(hashBuffer));
            return hashArray.map(b => ("00" + b.toString(16)).slice(-2)).join("");
        },
    }.freeze();
};

export interface Hash {
    
    hash(data: string): Promise<string>;
    
    hash(data: Buffer): Promise<string>;
    
}

export interface Sha {
    
    _1: Hash;
    
    _256: Hash;
    
    _384: Hash;
    
    _512: Hash;
    
}

export const SHA: Sha = <Sha> [1, 256, 384, 512]
    .reduce((obj: any, numBits: number) => ({...obj, ["_" + numBits]: makeSha(numBits)}), {})
    .freeze();