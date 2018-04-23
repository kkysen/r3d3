interface FlightSide {
    
    time(): Time;
    
    scheduledTime(): Time;
    
    delay(): Time;
    
    airport(): Airport;
    
}

type Departure = FlightSide;

type Arrival = FlightSide;

interface Flight {
    
    date(): Date;
    
    airline(): Airline;
    
    departure(): Departure;
    
    arrival(): Arrival;
    
    duration(): Time;
    
    scheduledDuration(): Time;
    
    distance(): number;
    
}

interface Airline {
    
    iataCode(): string;
    
    name(): string;
    
}

interface Airport {
    
    iataCode(): string;
    
    name(): string;
    
    city(): string;
    
    state(): string;
    
    country(): string;
    
    location(): GeoLocation;
    
    distanceTo(airport: Airport): number;
    
}

interface GeoLocation {
    
    longitude(): number;
    
    latitude(): number;
    
    distanceTo(location: GeoLocation): number;
    
}

interface Date {
    
    year(): number;
    
    dayOfYear(): number;
    
    month(): number;
    
    dayOfMonth(): number;
    
    week(): number;
    
    dayOfWeek(): number;
    
}

interface Time {
    
    minuteOfDay(): number;
    
    minuteOfHour(): number;
    
    hourOfDay(): number;
    
    isAM(): boolean;
    
    isPM(): boolean;
    
    add(time: Time): Time;
    
    subtract(time: Time): Time;
    
    negate(): Time;
    
}