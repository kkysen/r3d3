import {GeoProjection} from "d3-geo";
import {Map} from "./Map";
import {Selection} from "d3-selection";

export type CircleSelection = Selection<SVGCircleElement, any, SVGSVGElement, any>;

export interface GeoLocation {
    
    longitude(): number;
    
    latitude(): number;
    
    distanceTo(location: GeoLocation): number;
    
    coordinates(): Point;
    
    scale(): Point;
    
    plot(radius: number, color?: string): CircleSelection | null;

}

export const GeoLocation = {
    
    extendOn(location: GeoLocation): void {
        const prototype = Object.getPrototypeOf(location);
        
        if (prototype.extended) {
            return;
        }
        prototype.extended = true;
        
        prototype.coordinates = function(this: GeoLocation): Point {
            return [this.longitude(), this.latitude()];
        };
        
        const projection: GeoProjection = Map.projection;
        const svg = Map.svg;
        prototype.scale = function(this: GeoLocation): Point {
            return projection(this.coordinates());
        };
        
        prototype.plot = function(this: GeoLocation, radius: number, color?: string): CircleSelection | null {
            const point: Point = this.scale();
            if (!point) {
                // outside of US, like San Juan airport
                return null;
            }
            return <any> svg.append("circle")
                .attrs({
                    cx: point[0],
                    cy: point[1],
                    r: radius,
                    fill: color,
                });
        };
    },
    
};