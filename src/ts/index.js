var width = 700;
var height = 600;

var projection = d3.geo.albersUsa()
	.scale(1000)
	.translate([width / 2, height / 2]);
 
var path = d3.geo.path()
	.projection(projection);

var svg = d3.select("#map")
    .append("svg")
    .attr("width", width)
    .attr("height", height);

var states_info = []; 
var airports_info = []; 

d3.json("http://localhost:8000/states.json", function(error, states) {
    console.log("states:", states);
    console.log(states.features[0])

    var i = 0;

    while (states.features[i] != null) {
	states_info[i] = states.features[i];
	i++; 
    }

    console.log(states_info);
    
    svg.selectAll(".states")
	.data(states_info)
	.enter()
	.append("path")
	.attr("d", path);
});

d3.json("http://localhost:8000/airports.json", function(error, airports) {
    console.log("airports:", airports);
    console.log(airports.features[0])

    var i = 0;

    while (airportss.features[i] != null) {
	airports_info[i] = airports.features[i];
	i++; 
    }

    console.log(airports_info);
    
    svg.selectAll(".states")
	.data(airports_info)
	.enter()
	.append("path")
	.attr("d", path);
}); 


