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