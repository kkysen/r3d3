import {Airport} from "./Airport";
import {Flight, FlightSide} from "./Flight";
import {flights} from "./Flights";
import {Module} from "./wasm";

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
    
    flightFilter.addMethodFilter = function <T>(
        methods: string[], value: T, filter: (t1: T, t2: T) => boolean): FlightFilter {
        return flightFilter.addFilter(flight => {
            let accessed: any = flight;
            for (const method of methods) {
                accessed = accessed[method]();
            }
            return filter(accessed, value);
        });
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


const side = {
    time: "time",
    scheduledTime: "time",
    delay: "time",
    airport: "airport",
};

export interface FilterField<T> {
    
    inputType: string;
    
    convert(inputValue: string): T;
    
}

export interface HTMLAppendable<T> {
    
    appendTo(parent: HTMLElement): T;
    
}

interface DynamicFlightFilterField extends HTMLAppendable<DynamicFlightFilterField> {
    
    appendTo(parent: HTMLElement): DynamicFlightFilterField;
    
    onRemove(onRemove: () => void): void;
    
}

const newDynamicFlightFilterField = function(first: boolean): DynamicFlightFilterField {
    
    const div: HTMLDivElement = document.createElement("div");
    
    const functionHeader: string = !first
        ? "function filter(flight) {\n    \n}"
        : "function filter(flight) {\n    return flight.departure().airport().iataCode() === \"JFK;\"\n}"
    ;
    const codeBox: HTMLTextAreaElement = div.appendNewElement("code")
        .appendNewElement("textarea")
        .withInnerHTML(functionHeader);
    codeBox.cols = functionHeader.length;
    codeBox.rows = functionHeader.split("\n").length;
    
    div.appendBr();
    
    const compileAndAddButton: HTMLButtonElement = div.appendNewElement("button")
        .withInnerText("Compile and Add Filter Function");
    
    const removeButton: HTMLButtonElement = div.appendNewElement("button")
        .withInnerText("Remove");
    
    const error: HTMLParagraphElement = document.createElement("p")
        .withInnerText("Compile Error!");
    
    let functionBody: string = null;
    let func: FlightFilter = null;
    let funcUpdated = false;
    
    const getFunctionBody = function(): string {
        const code: string = codeBox.value;
        return code.substring(code.indexOf("{") + 1, code.lastIndexOf("}"));
    };
    
    const updateFunctionBody = function(): boolean {
        const newFunctionBody: string = getFunctionBody();
        if (functionBody && func && functionBody === newFunctionBody) {
            return false;
        }
        functionBody = newFunctionBody;
        funcUpdated = false;
        return true;
    };
    
    const compileAndAdd = function(): void {
        if (!updateFunctionBody() && funcUpdated) {
            return;
        }
        if (func) {
            func.remove();
        }
        funcUpdated = true;
        try {
            func = flightFilters.addDynamicFilter(functionBody);
            error.remove();
        } catch (e) {
            div.appendChild(error);
        }
    };
    
    compileAndAddButton.onclick = () => {
        compileAndAdd();
        compileAndAddButton.disabled = true;
    };
    
    codeBox.onkeypress = () => {
        if (updateFunctionBody()) {
            compileAndAddButton.disabled = false;
        }
    };
    
    let _onRemove: () => void = undefined;
    
    const remove = function(): void {
        div.remove();
        if (func) {
            func.remove();
        }
        if (_onRemove) {
            _onRemove();
        }
    };
    
    removeButton.onclick = () => remove();
    
    return {
        
        appendTo(parent: HTMLElement): DynamicFlightFilterField {
            parent.appendChild(div);
            return this;
        },
        
        onRemove(onRemove: () => void): void {
            _onRemove = onRemove;
        },
        
    };
};

interface DynamicFlightFilterFields extends HTMLAppendable<DynamicFlightFilterFields> {
    
    appendTo(parent: HTMLElement): DynamicFlightFilterFields;
    
}

const newDynamicFlightFilterFields = function(): DynamicFlightFilterFields {
    
    const div: HTMLDivElement = document.createElement("div");
    
    const title: HTMLHeadingElement = div.appendNewElement("h4")
        .withInnerText("Flight Filter Functions");
    
    const apiURL: string = "https://github.com/kkysen/r3d3/blob/master/src/ts/core/Flight.d.ts";
    const directions: HTMLParagraphElement = div.appendNewElement("p")
        .withInnerHTML([
            "You can write your own filter functions here to filter which flights are shown.",
            "Simply write a function: (flight: Flight) => boolean that returns if the flight should be shown or not.",
            "You can add more filter functions and remove the ones you have by clicking the buttons below.",
            "Click <code>Compile and Add Filter Function</code> to add the filter.",
            "Now when you click <code>Fly</code>, your filters will be applied.",
            "Click here for the <a href=\"" + apiURL + "\" target=\"_blank\">Flight API</a>.",
            "An example has been given below, which will show only flights leaving from JFK.",
        ].join("<br>"));
    
    const fields: HTMLDivElement = div.appendNewElement("div");
    
    div.appendBr();
    div.appendNewElement("hr");
    div.appendBr();
    const addNewFieldButton: HTMLButtonElement = div.appendNewElement("button")
        .withInnerText("Add New Filter");
    
    const addNewField = function(first: boolean = false): void {
        const field: DynamicFlightFilterField = newDynamicFlightFilterField(first);
        const br: HTMLBRElement = document.createElement("br");
        const hr: HTMLHRElement = document.createElement("hr");
        const elements: HTMLAppendable<any>[] = first ? [field] : [br, hr, field];
        elements.forEach(e => e.appendTo(fields));
        field.onRemove(() => {
            br.remove();
            hr.remove();
        });
    };
    
    addNewFieldButton.onclick = () => addNewField(false);
    
    addNewField(true); // start with 1
    
    return {
        
        appendTo(parent: HTMLElement): DynamicFlightFilterFields {
            parent.appendChild(div);
            return this;
        },
        
    };
    
};

const airportDropDownMenu = function(): void {
    const dropdown: HTMLSelectElement = document.createElement("select");
    document.body.appendChild(dropdown);
    const data: Airport[] = Module.Airport.all();
    dropdown.length = 0;
    
    const defaultOption: HTMLOptionElement = document.createElement("option");
    defaultOption.text = "Choose Airport";
    
    dropdown.add(defaultOption);
    dropdown.selectedIndex = 0;
    
    for (let i = 0; i < data.length; i++) {
        const option: HTMLOptionElement = document.createElement("option");
        const code: string = data[i].iataCode();
        console.log(data[i]);
        option.text = code;
        option.text = code;
        dropdown.add(option);
    }
};

export const createFlightFilterUI = function(): void {
    newDynamicFlightFilterFields().appendTo(document.body);
    
    // airportDropDownMenu();
};