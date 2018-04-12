export interface Time {
    
    minuteOfDay(): number;
    
    minuteOfHour(): number;
    
    hourOfDay(): number;
    
    isAM(): boolean;
    
    isPM(): boolean;
    
    add(time: Time): Time;
    
    subtract(time: Time): Time;
    
    negate(): Time;
    
}