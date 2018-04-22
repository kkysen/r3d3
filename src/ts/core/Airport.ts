import {CircleSelection, GeoLocation} from "./GeoLocation";
import {Module} from "./wasm";

export interface Airport {
    
    iataCode(): string;
    
    name(): string;
    
    city(): string;
    
    state(): string;
    
    country(): string;
    
    location(): GeoLocation;
    
    distanceTo(airport: Airport): number;
    
    plot(): CircleSelection | null;
    
    svg: CircleSelection;
    
}

const extendOn = function(airport: Airport): void {
    const prototype = Object.getPrototypeOf(airport);
    
    if (prototype.extended) {
        return;
    }
    prototype.extended = true;
    
    prototype.plot = function(this: Airport): CircleSelection | null {
        const circle: CircleSelection | null = this.location().plot(5, "blue");
        if (!circle) {
            return;
        }
        this.svg = circle;
        return circle.on("mouseover", () => {
            circle.append("title").text(this.iataCode() + ": " + this.name());
        });
    };
};

export const Airport = {
    
    extend(): void {
        (<any> Module.Airport).plotAll = function(): CircleSelection[] {
            return Module.Airport.all()
                .map(airport => airport.plot())
                .filter(e => e !== null);
        };
        extendOn(Module.Airport.of(0));
    },
    
};