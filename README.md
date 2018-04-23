# r3d3: Visualization of Airplane Flights and Delays in the US
by Team **r3d3**: Khyber Sen, Queenie Xiang, Anish Shenoy, and Kelly Wang

###
This project helps you visualize flight delays in the US (in 2015).

When you load the page, you should see a map of the United States
with a bunch of blue dots on it. These dots are all the airports in the US,
and if you hover over them, it will tell you what airport each of them are.

Above the map, you can choose the start and end dates for the flights
that you want to see. Since all of the 6 million flights in our dataset are in 2015,
the dates are restricted to 2015.
Once you choose dates, click ```Fly``` and watch as the airplanes take off.

There is a counter clock above the map showing you the current time.
The airplanes leave their departure airports and land at their arrival airports at the time shown.
In order to visualize the delay, every airplane is colored on a green-red gradient,
green being on time and red being late.
This delay color transitions as the airplane flies to its destination,
because there is a delay on takeoff and a delay on landing, which are transitioned between.
In the middle of the flight, the airplanes also become more transparent
so it's easier to focus on the other flights taking off and landing.

You can also filter all the flights in any way you want.
We give you the option of writing your own custom JavaScript function
that decides if a flight should be shown on the map, or if it should be skipped.
By letting you write your own custom filter functions,
it's possible to apply any sort of filter.
These filters can be found below the map, where there are more directions.
An example is given there, too.

## How To Run

  1. Clone this repository: ```git clone https://github.com/kkysen/r3d3.git```.
  2. Create a virtual environment using ```virtualenv``` or activate an existing one.
  3. In the virtual environment, cd into the repository
     and run ```make install``` to install dependencies
     and then ```make run``` to start the Flask server.
  4. With the flask app now running, navigate to ```localhost:5000``` in your browser.
     Because of a Flask bug, you may need to open a second tab to correctly load the first one.

## How to Compile

Most of this project was written in TypeScript and C++ (WebAssembly),
so if you want to change anything, you'll need to recompile everything.

To compile and bundle (using Webpack) the TypeScript and any other JavaScript, you need ```npm```.
Once ```npm``` is installed, run ```make compile-install``` to install ```npm``` dependencies.
Then run ```make js``` or ```npm run watch```,
which makes Webpack watch all the files and recompile them if anything changes.

To compile the C++ to WebAssembly,
you need the [Emscripten](https://kripken.github.io/emscripten-site/docs/getting_started/downloads.html) compiler.
Once ```emcc``` is installed, run ```make wasm``` to compile the C++ to WebAssembly and helper JS.
Webpack will then integrate the generated files into the final bundle.

## Bugs

There is a major Flask bug that we haven't been able to fix.
The Flask server for some reason doesn't see large HTTP requests sometimes,
causing our website to stall when loading the 50 MB flight data.
Since we were required to use Flask as our server, we couldn't get around this major bug.

However, it's pretty easy, although annoying, to circumvent it.
When another request is sent to Flask after it has stalled,
it is sometimes able to wake it up, upon which all the requests are responded to.
Our website automatically sends out random requests to the Flask server
trying to jumpstart it when it stalls, and so it may open a new tab at times.
You can close this; it's just trying to jumpstart Flask.
Given this bug, you may have to wait a little while before Flask is jumpstarted
and all the data is downloaded, but once it has, everything should be good.

## Data Sets

 * [Flight Delays - Kaggle](https://www.kaggle.com/usdot/flight-delays/data)
 
   This dataset contains information on the 6 million flights in 2015.
   It contains information on the airline, airports, times, and delays of each flight.

