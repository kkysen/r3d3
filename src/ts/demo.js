var svg = document.getElementById("svg");
var width = svg.getAttribute("width");
var height = svg.getAttribute("height");
var fly = document.getElementById("fly");

var xCoordinates = [830, 800, 50, 40, 350, 340, 480, 70, 140, 615, 800];
var yCoordinates = [155, 200, 300, 240, 280, 245, 350, 80, 300, 210, 250];



/*
Current airports:
Chicago, IL: ORD
NYC, NY: JFK
Oklahoma City, OK: OKC
Colorado Springs, CO: COS
Denver Internationl, CO: DEN
Philadelphia, PA: PHL
Washington National, DC: DCA
Las Vegas, NV: LAS
San Diego, CA: SAN
Los Angeles International, CA: LAX
Salem, OR: SLE
*/


console.log(svg);
console.log(width);
console.log(height);

/*
var plot = function() {
    for (i = 0; i < xCoordinates.length; i++) {
	      var c = document.createElementNS("http://www.w3.org/2000/svg", "circle");
        var plane = document.createElementNS("http://www.w3.org/2000/svg", "rect");

        plane.setAttribute("width", "10");
        plane.setAttribute("height", "10");
        plane.setAttribute("style", "fill:blue");
        
	      c.setAttribute("fill","lime");
	      c.setAttribute("r",5);
	      svg.appendChild(c);
        svg.appendChild(plane);
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

     var planes = d3.selectAll("rect");
     planes.data(xCoordinates);
     planes.attr("x", function(d){ return d; });
     planes.data(yCoordinates);
     planes.attr("y", function(d){ return d; });

}

var retInfo = function(e) {
    console.log(e.offsetX);
    console.log(e.offsetY);
    if ( (e.offsetX >= 795 && e.offsetX <= 805) && (e.offsetY >= 195 && e.offsetY <= 205) ) {
	console.log("Philadelphia, PA: PHL");
    }

    if ( (e.offsetX >= 825 && e.offsetX <= 835) && (e.offsetY >= 150 && e.offsetY <= 160) ) {
	console.log("NYC, NY: JFK");
    }

    if ( (e.offsetX >= 795 && e.offsetX <= 805) && (e.offsetY >= 245 && e.offsetY <= 255) ) {
	console.log("Washington National Airport, DC: DCA");
    }

    if ( (e.offsetX >= 45 && e.offsetX <= 55) && (e.offsetY >= 295 && e.offsetY <= 305) ) {
	console.log("Los Angeles International Airport, CA: LAX");
    }

    if ( (e.offsetX >= 135 && e.offsetX <= 145) && (e.offsetY >= 295 && e.offsetY <= 305) ) {
	console.log("Las Vegas, NV: LAS");
    }

}

var runAnimation = function() {
    var xStart = 830;
    var yStart = 155;

    var xEnd = 50;
    var yEnd = 290;

    for (xStart; xStart < xEnd; xStart += 5) {
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

    var planes = d3.selectAll("rect");
    planes.data(xCoordinates);
    planes.attr("x", function(d){ return d; });
    planes.data(yCoordinates);
    planes.attr("y", function(d){ return d; });

}


svg.addEventListener("click", retInfo);
fly.addEventListener("click",
  function(){
    var planes = d3.selectAll("rect");
    planes.data(xCoordinates)
  .transition().duration(2500)
  .attr("x", function(d,i){ return xCoordinates[(i+1) % xCoordinates.length] })
  .attr("y", function(d,i){ return yCoordinates[(i+1) % yCoordinates.length] });
  })

*/

var plot2 = function( lon, lat ){
    offlat = 124.456890;
    offlon = -24.044343;
    sizew = 57.0530243
    sizeh = 22.97928;
    
    xc = ((lat+offlat)/sizew) * width;
    yc = ((lon+offlon)/sizeh) * height;


    console.log(xc)
    console.log(yc)
    console.log("hh")
    
    var circle = document.createElementNS("http://www.w3.org/2000/svg", "circle");
    circle.setAttribute("cx", xc);
    circle.setAttribute("cy", height - yc);
    circle.setAttribute("r", 5);
    circle.setAttribute("fill", "green");
    svg.appendChild(circle);

    
}

//michigan
plot2( 45.07807, -83.56029);

//binghamton
plot2( 42.20848, -75.97961);

//buffalo
plot2( 42.94052, -78.73217);

//detroit
plot2( 42.21206, -83.34884);

//cleveland
plot2( 41.41089, -81.84940);

//dallas
plot2(32.89595, -97.03720);

//runAnimation();
