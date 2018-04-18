import {cachedFetch} from "../util/cachedFetch";
import {Module} from "./wasm";

const deleteNonContiguousStates = function(svg: SVGSVGElement) {
    const deletedStates: Set<string> = new Set(["HI", "AK"]); // Hawaii and Alaska
    [...svg.querySelectorAll("path")]
        .filter(path => deletedStates.has(path.id))
        .forEach(path => path.remove());
};

const setupMap = function(svg: SVGSVGElement) {
    deleteNonContiguousStates(svg);
    Module.GeoLocation.setScaleContinentalUS(svg.width.baseVal.value, svg.height.baseVal.value);
};

export const createMap = function() {
    const div = document.body.appendDiv();
    cachedFetch("map.svg")
        .then(response => response.text())
        .then(svg => {
            div.innerHTML = svg;
            return div.children[0];
        })
        .then(setupMap);
};