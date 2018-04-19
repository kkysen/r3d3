import {Airline} from "./Airline";
import {Airport} from "./Airport";
import {GeoLocation} from "./GeoLocation";
import {Time} from "./Time";
import {Date} from "./Date";
import {Range} from "../util/range";
import d3 = require("d3");


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
    
    render(): void;
    
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
        
        prototype.render = function(this: Flight): void {
            const departure: Departure = this.departure();
            const arrival: Arrival = this.arrival();
            
            const startDelay: number = departure.delay().minuteOfDay();
            const endDelay: number = arrival.delay().minuteOfDay();
            
            const duration: number = this.duration().minuteOfDay();
            
            const start: GeoLocation = departure.airport().location();
            const end: GeoLocation = arrival.airport().location();
            
            const endPoint: Point = end.scale();
            
            const startColor = mixColors(RED, GREEN, startDelay / 30);
            const endColor = mixColors(RED, GREEN, endDelay / 30);
            
            console.log({
                departure: departure,
                arrival: arrival,
                duration: duration,
                start: start,
                end: end,
                startDelay: startDelay,
                endDelay: endDelay,
                startColor: startColor,
                endColor: endColor,
            });
            
            const durationScale = 25;
            const plot = start.plot(5);
            if (!plot || !endPoint) {
                return;
            }
            plot.attrs({fill: startColor})
                .transition()
                .ease(d3.easeLinear)
                .duration(duration * durationScale)
                .attrs({
                    cx: endPoint[0],
                    cy: endPoint[1],
                    fill: endColor,
                });
        };
    },
    
};