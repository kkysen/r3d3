import {Flight} from "./Flight";
import {flights, flightsPromise} from "./Flights";
import {flightFilters} from "./FlightsFilter";
import {Map} from "./Map";

const animationFrame = function(): Promise<void> {
    return new Promise(resolve => requestAnimationFrame(() => resolve()));
};

let continueRenderingFlights: boolean = true;

export const renderFlightsInDay = async function(day: number, date: Date, updateDateTime: (date: Date) => void): Promise<void> {
    const flightsInDay: Flight[] = flights.get(day).toArray();
    flightsInDay.sortBy(flight => flight.departure().time().minuteOfDay());
    
    let flightNum: number = 0;
    let flight: Flight = flightsInDay[flightNum];
    const minutesInDay: number = 60 * 24;
    for (let minute: number = 0; minute < minutesInDay && flight && continueRenderingFlights; minute++) {
        await animationFrame();
        date.setHours(Math.floor(minute / 60), minute % 60);
        updateDateTime(date);
        while (continueRenderingFlights && flight && flight.departure().time().minuteOfDay() === minute) {
            if (flightFilters(flight)) {
                flight.render();
            }
            flight = flightsInDay[++flightNum];
        }
    }
};

export const renderFlights = async function(startDay: number, endDay: number, updateDateTime: (date: Date) => void): Promise<void> {
    startDay = Math.max(0, startDay);
    endDay = Math.min(365, endDay);
    for (let day = startDay; day < endDay && continueRenderingFlights; day++) {
        const flightDate = flights.get(day).toArray()[0].date();
        const date: Date = new Date(flightDate.year(), flightDate.month(), flightDate.dayOfMonth());
        await renderFlightsInDay(day, date, updateDateTime);
    }
};

export const stopRenderingFlights = function(stop: boolean = true): void {
    continueRenderingFlights = !stop;
};

(<any> window).renderFlightsInDay = renderFlightsInDay;
(<any> window).renderFlights = renderFlights;
(<any> window).stopRenderingFlights = stopRenderingFlights;

export const flier = function(): void {
    
    const div: HTMLDivElement = Map.header.node();
    const table: HTMLTableElement = div.appendNewElement("table");
    table.style.width = "100%";
    const row: HTMLTableRowElement = table.appendNewElement("tr");
    const newCell = function(): HTMLTableHeaderCellElement {
        return row.appendNewElement("th");
    };
    
    const dateInputs: HTMLInputElement[] = ["Start", "End"]
        .map(text => {
            const cell: HTMLTableHeaderCellElement = newCell();
            const label: HTMLLabelElement = cell.appendNewElement("label")
                .withInnerText(text);
            const input: HTMLInputElement = cell.appendNewElement("input");
            input.type = "date";
            input.min = "2015-01-01";
            input.max = "2015-12-31";
            input.value = text === "Start" ? input.min : text === "End" ? input.max : "";
            return input;
        });
    
    const dayOfYear = function(date: Date): number {
        const start: Date = new Date(date.getFullYear(), 0, 0);
        const diffMs: number = (<any> date - <any> start) + ((start.getTimezoneOffset() - date.getTimezoneOffset()) * 60 * 1000);
        const oneDayMs: number = 1000 * 60 * 60 * 24;
        return Math.floor(diffMs / oneDayMs) % 365;
    };
    
    const flyButton: HTMLButtonElement = newCell().appendButton("Fly!");
    const stopButton: HTMLButtonElement = newCell().appendButton("Cancel Flights");
    
    const currentDateTimeDisplay: HTMLHeadingElement = div.appendNewElement("center")
        .appendNewElement("h3");
    const updateDateTime = function(date: Date): void {
        currentDateTimeDisplay.innerText = date.toLocaleString();
    };
    
    flyButton.onclick = () => {
        stopRenderingFlights(false);
        const [start, end]: number[] = dateInputs.map(input => input.valueAsDate).map(dayOfYear);
        flightsPromise.get()
            .then(() =>
                renderFlights(start, end, updateDateTime)
                    .then(() =>
                        console.log("finished rendering flights")
                    )
            );
    };
    
    stopButton.onclick = () => stopRenderingFlights(true);
    
};