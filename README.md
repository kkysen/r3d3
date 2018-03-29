# r3d3

## Data Sets

 * [Monthly Tourism Statistics - National Travel and Tourism Office](https://travel.trade.gov/research/monthly/departures/)
   
   This dataset contains information on where US citizens are flying to.
   It divides the data by month and also offers statistics from multiple years.

 * [Flight Delays - Kaggle](https://www.kaggle.com/usdot/flight-delays/data)
 
   This dataset contains information on flight delays.
   The delays are tracked by airline, flight, and airport.

## How will the data come alive?

  1. Initially, the user will be shown a blank world map
     with dots scattered across representing the various airports in the world.
  
  2. Once the user hits begin, the animation will start and
     airplanes will begin to fly across the map to various countries.
     Planes originating from airports that are known to have delays
     will be slower and more pronounced in size and opacity.
     The animation will go through all of the months of the year and
     a progress bar will show what month the animation is currently on.
     The user can hover over airports to see more data about them and
     the number of flights that are leaving it.
  
  3. Our visualization will show users where people in the United States
     are actually travelling to. It will also show how prone certain areas are to delays.
     The visualization will provoke questions on why certain areas are popular
     among US residents and why certain areas are prone to delays.

## D3 feature utilization

   We plan to use enter selections to populate our map with airports initially.
   When animating the airplanes, we will have each plane have
   a certain speed, size, and transparency that will be determined by a data set.


The project would be similar to a [chloropleth](https://bl.ocks.org/mbostock/4060606) 
and a [click to zoom map](https://bl.ocks.org/mbostock/2206590) 


## Mock-Up

![Mock-up](http://geoawesomeness.com/wp-content/uploads/2015/11/US-Flights.jpg)
[Source](http://googletrends.github.io/iframe-scaffolder/#/s/01fJ5Q)
