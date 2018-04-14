const path = require("path");

module.exports = {
    entry: "./src/ts/main.js",
    output: {
        filename: "r3d3.js",
        // TODO changed from dist for testing, change back later
        path: path.resolve(__dirname, "src/cpp/BinaryFlightDelays/wasm"),
    },
    resolve: {
        extensions: [".ts", ".tsx", ".js"],
    },
    module: {
        rules: [
            {
                test: /\.tsx?$/,
                loader: "ts-loader",
            },
        ]
    },
    mode: "production",
};