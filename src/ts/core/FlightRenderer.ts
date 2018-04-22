import {min} from "d3-array";
import {Flight, FlightSide} from "./Flight";
import {flights} from "./Flights";

export interface FlightFilter {
    
    (flight: Flight): boolean;
    
    filters: ((flight: Flight) => boolean)[];
    
    add(filter: (flight: Flight) => boolean): void;
    
}

export const flightFilter: FlightFilter = (function() {
    const flightFilter: FlightFilter = <FlightFilter> function(flight: Flight): boolean {
        for (const filter of flightFilter.filters) {
            if (!filter(flight)) {
                return false;
            }
        }
        return true;
    };
    flightFilter.filters = [];
    flightFilter.add = function(filter: (flight: Flight) => boolean): void {
        flightFilter.filters.push(filter);
    };
    return flightFilter;
})();

(<any> window).flightFilter = flightFilter;

flightFilter.add(function inUS(flight: Flight): boolean {
    const inUS = function(side: FlightSide): boolean {
        return !!side.airport().location().scale();
    };
    return inUS(flight.departure()) && inUS(flight.arrival());
});

const animationFramePromise = function(): Promise<void> {
    return new Promise(resolve => requestAnimationFrame(() => resolve()));
};

let continueRenderingFlights: boolean = true;

export const renderFlightsInDay = async function(day: number): Promise<void> {
    const flightsInDay: Flight[] = flights.get(day).toArray();
    flightsInDay.sortBy(flight => flight.departure().time().minuteOfDay());
    
    let flightNum: number = 0;
    let flight: Flight = flightsInDay[flightNum];
    const minutesInDay: number = 60 * 24;
    for (let minute: number = 0; minute < minutesInDay && flight && continueRenderingFlights; minute++) {
        await animationFramePromise();
        console.log(Math.floor(minute / 60) + ":" + minute % 60);
        while (continueRenderingFlights && flight && flight.departure().time().minuteOfDay() === minute) {
            if (flightFilter(flight)) {
                flight.render();
            }
            flight = flightsInDay[++flightNum];
        }
    }
};

export const renderFlights = async function(startDay: number, endDay: number): Promise<void> {
    startDay = Math.max(0, startDay);
    endDay = Math.min(365 - 1, endDay);
    for (let day = startDay; day <= endDay && continueRenderingFlights; day++) {
        await renderFlightsInDay(day);
    }
};

export const stopRenderingFlights = function(stop: boolean = true): void {
    continueRenderingFlights = !stop;
};

(<any> window).renderFlightsInDay = renderFlightsInDay;
(<any> window).renderFlights = renderFlights;
(<any> window).stopRenderingFlights = stopRenderingFlights;

(<any> window).run = async function() {
    console.time("render");
    await renderFlightsInDay(0);
    console.timeEnd("render");
};