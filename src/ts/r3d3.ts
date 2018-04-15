import {flights} from "./core/Flights";
import {postWasm, runAfterWasm} from "./core/wasm";

const realMain = function() {
    console.log("realMain");
    flights.get()
        .then(flights => {
            console.log(flights);
        });
};

export const main = function() {
    [postWasm, realMain].forEach(runAfterWasm);
};