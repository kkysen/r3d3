"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const ReattachingBuffer_1 = require("../util/ReattachingBuffer");
const range_1 = require("../util/range");
const wasm_1 = require("./wasm");
const map_1 = require("./map");
const d3 = require("d3");
exports.ProjectionMarshaller = (function () {
    const convertProjection = function (Flight, jsProjection) {
        const newProjectedLocation = function () {
            return new Float64Array(wasm_1.Module.HEAP, Flight.projectedLocationPointer(), Flight.projectedLocationSize() / Float64Array.BYTES_PER_ELEMENT);
        };
        const projectedLocation = window.projectedLocation =
            ReattachingBuffer_1.ReattachingBuffer.new(newProjectedLocation, wasm_1.Module.wasmMemory, "grow");
        const wasmProjection = function () {
            const point = jsProjection(projectedLocation.get());
            if (point) {
                projectedLocation[0] = point[0];
                projectedLocation[1] = point[1];
            }
            else {
                console.log(projectedLocation + " is not in US");
                projectedLocation[0] = projectedLocation[1] = NaN;
            }
        };
        return wasm_1.Module.addFunction(wasmProjection, "v");
    };
    return {
        extendOn(Flight) {
            const wasmSetProjection = Flight.setProjectionPointer;
            Flight.setProjection = function (projection) {
                wasmSetProjection(convertProjection(Flight, projection));
            };
            Flight.setProjection(map_1.Map.projection);
        },
    };
})();
const createFlightInterpolatorState = function () {
    const state = new DataView(wasm_1.Module.HEAP, wasm_1.Module.FlightInterpolator.statePointer(), wasm_1.Module.FlightInterpolator.stateSize());
    const floatSize = 4;
    const byteSize = 1;
    return {
        get opacity() {
            // noinspection PointlessArithmeticExpressionJS
            return state.getFloat32(floatSize * 0, true);
        },
        position: {
            get x() {
                // noinspection PointlessArithmeticExpressionJS
                return state.getFloat32(floatSize * 1, true);
            },
            get y() {
                return state.getFloat32(floatSize * 2, true);
            },
            toArray() {
                return [this.x, this.y];
            },
        },
        color: {
            get r() {
                // noinspection PointlessArithmeticExpressionJS
                return state.getUint8(floatSize * 3 + byteSize * 0);
            },
            get g() {
                // noinspection PointlessArithmeticExpressionJS
                return state.getUint8(floatSize * 3 + byteSize * 1);
            },
            get b() {
                return state.getUint8(floatSize * 3 + byteSize * 2);
            },
            get red() {
                return this.r;
            },
            get green() {
                return this.g;
            },
            get blue() {
                return this.b;
            },
            rgbString() {
                return "rgb(" + this.r + "," + this.g + "," + this.b + ")";
            },
        },
        opacityTween: (flight) => () => () => {
            // must call flight.render() once to update all attrs
            flight.render();
            return this.opacity;
        },
        cxTween: () => () => this.position.x,
        cyTween: () => () => this.position.y,
        colorTween: () => () => this.color.rgbString(),
    };
};
exports.setFlightInterpolatorState = function () {
    exports.FlightInterpolatorState = createFlightInterpolatorState();
};
exports.Flight = {
    extendOn(flight) {
        const prototype = Object.getPrototypeOf(flight);
        if (prototype.extended) {
            return;
        }
        prototype.extended = true;
        const RED = [255, 0, 0];
        const GREEN = [0, 255, 0];
        const mixColors = function (color1, color2, weight) {
            if (weight < 0) {
                weight = 0;
            }
            if (weight > 1) {
                weight = 1;
            }
            const weight1 = weight;
            const weight2 = 1 - weight;
            return "rgb("
                + range_1.Range.new(3).map(i => Math.round(color1[i] * weight1 + color2[i] * weight2))
                    .join(",")
                + ")";
        };
        prototype.render = function () {
            const interpolator = this.interpolator();
            const state = exports.FlightInterpolatorState;
            return map_1.Map.svg
                .append("circle")
                .attrs({ r: 5 })
                .transition()
                .ease(d3.easeLinear)
                .duration(interpolator.duration())
                .styleTween("opacity", state.opacityTween(flight))
                .attrTween("cx", state.cxTween)
                .attrTween("cy", state.cyTween)
                .attrTween("fill", state.colorTween);
        };
        prototype.render = function () {
            const departure = this.departure();
            const arrival = this.arrival();
            const startDelay = departure.delay().minuteOfDay();
            const endDelay = arrival.delay().minuteOfDay();
            const duration = this.duration().minuteOfDay();
            const start = departure.airport().location();
            const end = arrival.airport().location();
            const endPoint = end.scale();
            const startColor = mixColors(RED, GREEN, startDelay / 30);
            const endColor = mixColors(RED, GREEN, endDelay / 30);
            console.log({
                departure: departure,
                arrival: arrival,
                duration: duration,
                start: start,
                end: end,
                startDelay: startDelay,
                endDelay: endDelay,
                startColor: startColor,
                endColor: endColor,
            });
            if (!start.scale() || !endPoint) {
                return;
            }
            // TODO can use attrTween to supply custom wasm interpolator
            const durationScale = 25;
            const plot = start.plot(5);
            plot.attrs({ fill: startColor })
                .transition()
                .ease(d3.easeLinear)
                .duration(duration * durationScale)
                .attrTween("", () => () => "")
                .attrs({
                cx: endPoint[0],
                cy: endPoint[1],
                fill: endColor,
            });
        };
    },
};
//# sourceMappingURL=Flight.js.map