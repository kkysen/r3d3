import {GeoPath, GeoProjection} from "d3-geo";
import {FeatureCollection} from "geojson";
import {cachedFetch} from "../util/cachedFetch";
import {Module} from "./wasm";
import {Selection} from "d3-selection";
import d3 = require("d3");
import d3multi = require("d3-selection-multi");

console.log(d3multi);

const deleteNonContiguousStates = function(svg: SVGSVGElement) {
    const deletedStates: Set<string> = new Set(["HI", "AK"]); // Hawaii and Alaska
    [...svg.querySelectorAll("path")]
        .filter(path => deletedStates.has(path.id))
        .forEach(path => path.remove());
};

export interface Map {
    
    readonly projection: GeoProjection;
    readonly path: GeoPath<SVGPathElement, any>;
    readonly svg: Selection<SVGSVGElement, any, any, any>;
    
}

const projection: GeoProjection = d3.geoAlbersUsa();
const path: GeoPath<SVGPathElement, any> = d3.geoPath(projection);
const svg: Selection<SVGSVGElement, any, any, any> = d3.select(document.body).append("svg");

export const Map: Map = {
    
    projection: projection,
    
    path: path,
    
    svg: svg,
    
};

(<any> window).map = Map;

export const createMap = function() {
    svg.attrs({
        width: 1000,
        height: 1000,
    });
    
    const name = "states";
    
    cachedFetch("data/" + name + ".json")
        .then(response => response.json())
        .then(json => json as FeatureCollection<{type: "MultiPolygon" | "Polygon"}>)
        .then(features => features.features)
        .then(features => svg
            .selectAll(".states")
            .data(features)
            .enter()
            .append("path")
            .attrs({
                d: path,
                stroke: "white",
            })
        );
    
    // cachedFetch("map.svg")
    //     .then(response => response.text())
    //     .then(svg => {
    //         div.innerHTML = svg;
    //         return div.children[0];
    //     })
    //     .then(setupMap);
};

const setupMap = function(svg: SVGSVGElement) {
    deleteNonContiguousStates(svg);
    Module.GeoLocation.setScaleContinentalUS(svg.width.baseVal.value, svg.height.baseVal.value);
};
