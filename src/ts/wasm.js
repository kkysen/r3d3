const importObject = {
    imports: {
        imported_func: function(arg) {
            console.log(arg);
        }
    }
};

fetch("../cpp/BinaryFlightDelays/CompactFlights.wasm")
    .then(response => response.arrayBuffer())
    .then(bytes => WebAssembly.instantiate(bytes, importObject))
    .then(result => {
        console.log(result);
    });