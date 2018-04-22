"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const cachedFetch_1 = require("../util/cachedFetch");
const wasm_1 = require("./wasm");
const d3 = require("d3");
const d3multi = require("d3-selection-multi");
console.log(d3multi);
const deleteNonContiguousStates = function (svg) {
    const deletedStates = new Set(["HI", "AK"]); // Hawaii and Alaska
    [...svg.querySelectorAll("path")]
        .filter(path => deletedStates.has(path.id))
        .forEach(path => path.remove());
};
const projection = d3.geoAlbersUsa();
const path = d3.geoPath(projection);
const svg = d3.select(document.body).append("svg");
exports.Map = {
    projection: projection,
    path: path,
    svg: svg,
};
window.map = exports.Map;
exports.createMap = function () {
    svg.attrs({
        width: 1000,
        height: 1000,
    });
    const name = "states";
    cachedFetch_1.cachedFetch("data/" + name + ".json")
        .then(response => response.json())
        .then(json => json)
        .then(features => features.features)
        .then(features => svg
        .selectAll(".states")
        .data(features)
        .enter()
        .append("path")
        .attrs({
        d: path,
        stroke: "white",
    }));
    // cachedFetch("map.svg")
    //     .then(response => response.text())
    //     .then(svg => {
    //         div.innerHTML = svg;
    //         return div.children[0];
    //     })
    //     .then(setupMap);
};
const setupMap = function (svg) {
    deleteNonContiguousStates(svg);
    wasm_1.Module.GeoLocation.setScaleContinentalUS(svg.width.baseVal.value, svg.height.baseVal.value);
};
//# sourceMappingURL=map.js.map