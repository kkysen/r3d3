import {Class} from "./class";

// TODO addFilter types
export const Converter = Class.new((fieldConverters = {}, defaultConverter = Number, defaultValue = 0) => {
        return o => {
            for (const field in o) {
                if (o.hasOwnProperty(field)) {
                    // convert using fieldConverters (default Number) and replace any NaNs with 0s
                    o[field] = (fieldConverters[field] || defaultConverter)(o[field]) || defaultValue;
                }
            }
            return o;
        };
    }
);