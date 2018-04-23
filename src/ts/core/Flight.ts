import {Transition} from "d3-transition";
import {Selection} from "d3-selection";
import {ReattachingBuffer} from "../util/ReattachingBuffer";
import {Airline} from "./Airline";
import {Airport} from "./Airport";
import {Color} from "./Color";
import {CircleSelection, GeoLocation} from "./GeoLocation";
import {Time} from "./Time";
import {Date} from "./Date";
import {Range} from "../util/range";
import {Vector} from "./Vector";
import {FlightClass, Module} from "./wasm";
import {Map} from "./Map";
import d3 = require("d3");

export const ProjectionMarshaller: {
    
    extendOn(Flight: FlightClass): void;
    
} = (function() {
    
    type WasmProjection = number;
    type JSProjection = (geoLocation: Point) => Point;
    
    const convertProjection = function(Flight: FlightClass, jsProjection: JSProjection): WasmProjection {
        type ProjectedLocation = Float64Array & Point;
        
        const getProjectedLocation = function(): ProjectedLocation {
            return <ProjectedLocation> new Float64Array(Module.HEAP,
                Flight.projectedLocationPointer(),
                Flight.projectedLocationSize() / Float64Array.BYTES_PER_ELEMENT);
        };
        
        const reattachingProjectedLocation: ReattachingBuffer<ProjectedLocation> = (<any> window).projectedLocation =
            ReattachingBuffer.onWasmMemoryGrowth(getProjectedLocation);
        
        const wasmProjection = function(): void {
            const projectedLocation: ProjectedLocation = reattachingProjectedLocation.get();
            // console.log(projectedLocation);
            const point: Point = jsProjection(projectedLocation);
            if (point) {
                // console.log(point);
                projectedLocation[0] = point[0];
                projectedLocation[1] = point[1];
                // console.log(projectedLocation);
            } else {
                console.log(projectedLocation + " is not in US");
                projectedLocation[0] = projectedLocation[1] = NaN;
            }
        };
        
        return Module.addFunction(wasmProjection, "v");
        
    };
    
    return {
        
        extendOn(Flight: FlightClass): void {
            const wasmSetProjection: (projection: WasmProjection) => void = Flight.setProjectionPointer;
            Flight.setProjection = function(projection: JSProjection) {
                wasmSetProjection(convertProjection(Flight, <JSProjection> projection));
            };
            Flight.setProjection(Map.projection);
        },
        
    };
    
})();

type Tween = () => (time: number) => string;

export interface FlightInterpolatorState {
    
    readonly opacity: number;
    readonly position: Vector;
    readonly color: Color;
    
    readonly opacityTween: (flight: Flight) => Tween;
    readonly cxTween: Tween;
    readonly cyTween: Tween;
    readonly colorTween: Tween;
    
}

const createFlightInterpolatorState = function(): FlightInterpolatorState {
    
    const getState = function(): DataView {
        return new DataView(Module.HEAP,
            Module.FlightInterpolator.statePointer(), Module.FlightInterpolator.stateSize());
    };
    
    const reattachingState: ReattachingBuffer<DataView> = ReattachingBuffer.onWasmMemoryGrowth(getState);
    let rawState: DataView;
    
    const floatSize = 4;
    const byteSize = 1;
    
    const state: FlightInterpolatorState & any = {
        
        get opacity(): number {
            rawState = reattachingState.get(); // first call
            // noinspection PointlessArithmeticExpressionJS
            return rawState.getFloat32(floatSize * 0, true);
        },
        
        position: {
            get x(): number {
                // noinspection PointlessArithmeticExpressionJS
                return rawState.getFloat32(floatSize * 1, true);
            },
            get y(): number {
                return rawState.getFloat32(floatSize * 2, true);
            },
            
            toArray(): Point {
                return [this.x, this.y];
            },
        },
        
        color: {
            get r(): number {
                // noinspection PointlessArithmeticExpressionJS
                return rawState.getUint8(floatSize * 3 + byteSize * 0);
            },
            get g(): number {
                // noinspection PointlessArithmeticExpressionJS
                return rawState.getUint8(floatSize * 3 + byteSize * 1);
            },
            get b(): number {
                return rawState.getUint8(floatSize * 3 + byteSize * 2);
            },
            
            get red(): number {
                return this.r;
            },
            get green(): number {
                return this.g;
            },
            get blue(): number {
                return this.b;
            },
            
            rgbString(): string {
                return "rgb(" + this.r + "," + this.g + "," + this.b + ")";
            },
        },
        
        opacityTween: function(flight: Flight): Tween {
            const interpolator: FlightInterpolator = flight.interpolator();
            return () => (time: number) => {
                // interpolator.interpolate() updates all state values, which are accessed after opacity
                // interpolator.update(); // TODO may want to pass time here
                interpolator.interpolate(time);
                return state.opacity.toString();
            };
        },
        
        cxTween: () => () => state.position.x,
        
        cyTween: () => () => state.position.y,
        
        colorTween: () => () => state.color.rgbString(),
        
    };
    
    return state;
    
};

export let FlightInterpolatorState: FlightInterpolatorState;

export const setFlightInterpolatorState = function(): void {
    FlightInterpolatorState = createFlightInterpolatorState();
};

export interface FlightInterpolator {
    
    duration(): number;
    
    interpolate(time: number): void;
    
    update(): void;
    
}

export interface FlightSide {
    
    time(): Time;
    
    scheduledTime(): Time;
    
    delay(): Time;
    
    airport(): Airport;
    
}

export type Departure = FlightSide;

export type Arrival = FlightSide;

export interface Flight {
    
    date(): Date;
    
    airline(): Airline;
    
    departure(): Departure;
    
    arrival(): Arrival;
    
    duration(): Time;
    
    scheduledDuration(): Time;
    
    distance(): number;
    
    interpolator(): FlightInterpolator;
    
    render(): void;
    
    wasmRender(): Transition<SVGCircleElement, any, SVGSVGElement, any>;
    
    jsRender(): Transition<SVGPathElement, any, SVGSVGElement, any>;
    
}

export const Flight = {
    
    extendOn(flight: Flight) {
        const prototype = Object.getPrototypeOf(flight);
        
        if (prototype.extended) {
            return;
        }
        prototype.extended = true;
        
        type Color = [number, number, number];
        
        const RED: Color = [255, 0, 0];
        const GREEN: Color = [0, 255, 0];
        
        prototype.wasmRender = function(this: Flight): Transition<SVGCircleElement, any, SVGSVGElement, any> {
            const interpolator: FlightInterpolator = this.interpolator();
            const state: FlightInterpolatorState = FlightInterpolatorState;
            return <any> Map.svg
                .append("circle")
                .attrs({r: 5})
                .transition()
                .ease(d3.easeLinear)
                .duration(interpolator.duration())
                .styleTween("opacity", state.opacityTween(flight))
                .attrTween("cx", state.cxTween)
                .attrTween("cy", state.cyTween)
                .attrTween("fill", state.colorTween)
                .remove();
        };
        
        const mixColors = function(color1: Color, color2: Color, weight: number): string {
            if (weight < 0) {
                weight = 0;
            }
            if (weight > 1) {
                weight = 1;
            }
            const weight1 = weight;
            const weight2 = 1 - weight;
            return "rgb("
                + Range.new(3).map(i => Math.round(color1[i] * weight1 + color2[i] * weight2))
                    .join(",")
                + ")";
        };
        
        const translate = function(point: Point): string {
            return "translate(" + Number.toPixels(point[0]) + "," + Number.toPixels(point[1]) + ")";
        };
        
        const millis = function(time: number): string {
            return Math.round(time * 1000) + "ms";
        };
        
        prototype.jsRender = function(this: Flight): Transition<SVGPathElement, any, SVGSVGElement, any> {
            const departure: Departure = this.departure();
            const arrival: Arrival = this.arrival();
            
            const startDelay: number = departure.delay().minuteOfDay();
            const endDelay: number = arrival.delay().minuteOfDay();
            
            const duration: number = this.duration().minuteOfDay();
            
            const start: GeoLocation = departure.airport().location();
            const end: GeoLocation = arrival.airport().location();
            
            const startPoint: Point = start.scale();
            const endPoint: Point = end.scale();
            
            const startColor = mixColors(RED, GREEN, startDelay / 30);
            const endColor = mixColors(RED, GREEN, endDelay / 30);
            
            const log = {
                departure: departure,
                arrival: arrival,
                duration: duration,
                start: start,
                end: end,
                startDelay: startDelay,
                endDelay: endDelay,
                startColor: startColor,
                endColor: endColor,
            };
            // console.log(log);
            
            if (!startPoint || !endPoint) {
                return;
            }
            
            const airplaneSvgData: string = "M510,255c0-20.4-17.85-38.25-38.25-38.25H331.5L204,12.75h-51l63.75,204H76.5l-38.25-51H0L25.5,255L0,344.25h38.25\n" +
                "\t\t\tl38.25-51h140.25l-63.75,204h51l127.5-204h140.25C492.15,293.25,510,275.4,510,255z";
            
            const durationScale = 25;
            const minOpacity = .5;
            
            const angle: number = Math.atan2(endPoint[1] - startPoint[1], endPoint[0] - startPoint[0]);
            const rotation: string = "rotate(" + angle + "rad)";
            
            const scale: string = "scale(" + 0.05 + ")";
            
            const airplane: Selection<SVGPathElement, any, SVGSVGElement, any> = <any> Map.svg
                .append("path")
                .attrs({
                    d: airplaneSvgData,
                })
                .styles({
                    fill: startColor,
                    transform: [translate(startPoint), scale, rotation].join(" "),
                });
            
            if (Module.Flight.useCSSTransitions) {
                // CSS transitions should be faster b/c use GPU efficiently
                throw new Error("not implemented yet");
            } else {
                return <Transition<SVGPathElement, any, SVGSVGElement, any>>
                    airplane
                        .transition()
                        .ease(d3.easeLinear)
                        .duration(duration * durationScale)
                        .styleTween("opacity", () => (t: number) => {
                            return ((2 / minOpacity * t - 1) ** 2).toString();
                        })
                        .styles({
                            fill: endColor,
                            transform: [translate(endPoint), scale, rotation].join(" "),
                        });
            }
        };
        
        const showAirportDelay = function(side: FlightSide): void {
            const svg: CircleSelection = side.airport().svg;
            const delay: number = side.delay().minuteOfDay();
            // TODO
        };
        
        prototype.render = function(this: Flight): void {
            this.jsRender()
                .on("start", () => showAirportDelay(this.departure()))
                .on("end", () => showAirportDelay(this.arrival()))
                .remove()
            ;
        };
    },
    
};