import {Class} from "./class";

type NumberFunc = (number) => number;

type RepeaterFunc<T> = (repeatNum: number, interval: number) => T;

type StopCondition = RepeaterFunc<boolean>;

type RepeaterCallback = RepeaterFunc<void>;

export interface Cancellable {
    
    cancel(): void;
    
}

export type CancellablePromise<T> = Promise<T> & Cancellable;

export interface Repeater {
    
    interval(interval: number): Repeater;
    
    interval(interval: NumberFunc): Repeater;
    
    until(stopCondition: StopCondition): Repeater;
    
    numRepeats(numRepeats: number): Repeater;
    
    noInitialDelay(noDelay?: boolean): Repeater;
    
    calling(callback: RepeaterCallback): Repeater;
    
    start(): CancellablePromise<void>;
    
}

export type RepeaterClass = {
    
    new: () => Repeater;
    
}

export const Repeater: RepeaterClass = Class.new(() => {
    
    let _interval: NumberFunc = () => 0;
    let _stopCondition: StopCondition = () => false;
    let _callback: RepeaterCallback = () => undefined;
    let _initialDelay: boolean = true;
    
    return Object.freeze({
        
        interval(interval: number | NumberFunc): Repeater {
            let intervalFunc: NumberFunc;
            if (typeof interval === "number") {
                const intervalValue: number = <number> interval;
                intervalFunc = () => intervalValue;
            } else {
                intervalFunc = <NumberFunc> interval;
            }
            _interval = i => intervalFunc(i) * 1000; // use seconds, not ms
            return this;
        },
        
        until(stopCondition: StopCondition): Repeater {
            _stopCondition = stopCondition;
            return this;
        },
        
        numRepeats(numRepeats: number): Repeater {
            if (numRepeats < 0) {
                numRepeats = 0;
            }
            return this.until(i => i >= numRepeats);
        },
        
        noInitialDelay(noDelay: boolean = true): Repeater {
            _initialDelay = !noDelay;
            return this;
        },
        
        calling(callback: RepeaterCallback): Repeater {
            _callback = callback;
            return this;
        },
        
        start(): CancellablePromise<void> {
            const interval: NumberFunc = _interval;
            const stopCondition: StopCondition = _stopCondition;
            const callback: RepeaterCallback = _callback;
            const initialDelay: boolean = _initialDelay;
            
            const ids: number[] = [];
            
            type R = CancellablePromise<void>;
            
            const promise: R = <R> <any> new Promise(resolve => (function runOnce(i: number) {
                const currentInterval: number = interval(i);
                // console.log("currentInterval: " + currentInterval);
                const id: number = setTimeout(() => {
                    if (stopCondition(i, currentInterval)) {
                        resolve();
                        return;
                    }
                    callback(i, currentInterval);
                    runOnce(i + 1);
                }, !initialDelay && i === 0 ? 0 : currentInterval);
                ids.push(id);
            })(0));
            
            promise.cancel = () => ids.forEach(clearTimeout);
            
            return promise;
        },
        
    });
    
});