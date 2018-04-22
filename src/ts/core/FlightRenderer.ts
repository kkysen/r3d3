import {Flight} from "./Flight";
import {flights} from "./Flights";

const animationFramePromise = function(): Promise<void> {
    return new Promise(resolve => requestAnimationFrame(() => resolve()));
};

export const renderFlightsInDay = async function(day: number): Promise<void> {
    const flightsInDay: Flight[] = flights.get(day).toArray();
    flightsInDay.sortBy(flight => flight.departure().time().minuteOfDay());
    
    let flightNum: number = 0;
    let flight: Flight = flightsInDay[flightNum];
    const minutesInDay: number = 60 * 24;
    for (let minute: number = 0; minute < minutesInDay && flightNum < flightsInDay.length; minute++) {
        await animationFramePromise();
        console.log(Math.floor(minute / 60) + ":" + minute % 60);
        while (flight.departure().time().minuteOfDay() === minute) {
            flight.render();
            flight = flightsInDay[++flightNum];
        }
    }
};


export const renderFlights = async function(startDay: number, endDay: number): Promise<void> {
    for (let day = startDay; day <= endDay; day++) {
        await renderFlightsInDay(day);
    }
};

(<any> window).renderFlightsInDay = renderFlightsInDay;
(<any> window).renderFlights = renderFlights;