import {Flight, FlightSide} from "./Flight";
import {flights} from "./Flights";

type BasicFlightFilter = (flight: Flight) => boolean;

export interface FlightFilter extends BasicFlightFilter {
    
    index: number;
    
    remove(): void;
    
}

export interface FlightFilters {
    
    (flight: Flight): boolean;
    
    filters: FlightFilter[];
    
    addFilter(filter: BasicFlightFilter): FlightFilter;
    
    addMethodFilter<T>(properties: string[], value: T, filter: (t1: T, t2: T) => boolean): FlightFilter;
    
    addDynamicFilter(functionBody: string): FlightFilter;
    
}

export const flightFilters: FlightFilters = (function() {
    const filters = [];
    
    const flightFilter: FlightFilters = <FlightFilters> function(flight: Flight): boolean {
        for (const filter of filters) {
            if (!filter(flight)) {
                return false;
            }
        }
        return true;
    };
    
    flightFilter.filters = filters;
    
    flightFilter.addFilter = function(rawFilter: BasicFlightFilter): FlightFilter {
        const filter: FlightFilter = <FlightFilter> rawFilter;
        filter.index = filters.length;
        
        filter.remove = function(): void {
            filters.splice(filter.index, 1);
            for (let i = filter.index; i < filters.length; i++) {
                filters[i].index--;
            }
        };
        
        filters.push(filter);
        return filter;
    };
    
    flightFilter.addMethodFilter = function<T>(properties: string[], value: T, filter: (t1: T, t2: T) => boolean): FlightFilter {
    
    };
    
    flightFilter.addDynamicFilter = function(functionBody: string): FlightFilter {
        const filter: BasicFlightFilter = <BasicFlightFilter> new Function("flight", functionBody);
        const returnValue: any = filter(flights.flight(0, 0)); // to catch errors
        if (typeof returnValue !== "boolean") {
            throw new Error("return value of FlightFilter must be a boolean: " + filter);
        }
        return flightFilter.addFilter(filter);
    };
    
    return flightFilter;
})();

(<any> window).flightFilters = flightFilters;

flightFilters.addFilter(function inUS(flight: Flight): boolean {
    const inUS = function(side: FlightSide): boolean {
        return !!side.airport().location().scale();
    };
    return inUS(flight.departure()) && inUS(flight.arrival());
});