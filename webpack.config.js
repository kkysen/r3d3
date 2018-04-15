const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");

module.exports = {
    node: {
        fs: "empty",
    },
    entry: {
        wasm: "./src/cpp/BinaryFlightDelays/wasm/js/CompactFlights.js",
        r3d3: "./src/ts/main.js",
    },
    output: {
        filename: "[name].js",
        path: path.resolve(__dirname, "dist"),
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
    plugins: [
        new HtmlWebpackPlugin({
            hash: true,
            filename: "index.html",
            template: "./src/html/index.html",
        }),
    ],
    mode: "development",
};