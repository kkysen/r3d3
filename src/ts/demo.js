var svg = document.getElementById("svg");
var width = svg.getAttribute("width");
var height = svg.getAttribute("height");

var xCoordinates = [800, 830, 830, 835,  50, 40, 350, 340];
var yCoordinates = [200, 150, 155, 145, 250, 240, 280, 245];


console.log(svg);
console.log(width);
console.log(height);


var plot = function() {
    for (i = 0; i < xCoordinates.length; i++) {
	var c = document.createElementNS("http://www.w3.org/2000/svg", "circle");

	c.setAttribute("fill","lime");
	c.setAttribute("r",5);
	svg.appendChild(c);
    }

    var circles = d3.selectAll("circle");
    circles.data(xCoordinates);
    circles.attr("cx",
		 function(d) {
		     return d; });
    
    circles.data(yCoordinates);
    circles.attr("cy",
		 function(d) {
		     return d; });

}	

plot();
