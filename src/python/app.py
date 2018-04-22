from __future__ import print_function

import os

from flask import Flask, Response, render_template, send_from_directory, send_file

app = Flask(__name__, root_path=os.path.abspath("../../dist"), template_folder="", static_folder="", static_url_path="")


@app.route("/")
def r3d3():
    # type: () -> Response
    # map(print, app.url_map.iter_rules())
    return render_template("index.html")


def make_data_route(app, route, path, mime_type=None):
    # type: (Flask, str, str, str) -> None
    def data():
        # type: () -> Response
        print(route)
        return send_file(os.path.abspath(path), mimetype=mime_type)
        # return Response(response=open(path).read(), mimetype=mime_type)
    
    data.func_name = route
    app.route("/" + route)(data)


def make_file_data_route(filename, dir, prefix=""):
    # type: (str, str) -> None
    dir = "../" + dir
    _, extension = filename.split(".")
    route = filename
    mime_type = {
        "bin": "application/octet-stream",
        "csv": "text/csv",
        "wasm": "application/wasm",
        "svg": "image/svg+xml",
        "json": "application/json",
    }[extension]
    path = dir + "/" + filename
    if prefix:
        route = prefix + "/" + route
    make_data_route(app, route, path, mime_type)


map(lambda filename: make_file_data_route(filename, "data/flight-delays", "data"),
    ["flights.bin", "airports.csv", "airlines.csv"])
make_file_data_route("CompactFlights.wasm", "cpp/BinaryFlightDelays/wasm/js", "")
make_file_data_route("map.svg", "data", "")
map(lambda filename: make_file_data_route(filename, "data/", "data"),
    ["airports.json", "cities.json", "countries.json", "states.json"])

# @app.route("/src/<path:filename>")
# def src_file(filename):
#     # type: (str) -> Response
#     print(filename)
#     return send_from_directory(os.path.abspath(".."), filename)

app.secret_key = os.urandom(32)
app.debug = True

if __name__ == '__main__':
    app.run()
