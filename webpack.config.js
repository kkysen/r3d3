const path = require("path");

module.exports = {
    entry: "./src/r3d3.js",
    output: {
        filename: "r3d3.js",
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
    mode: "production",
};