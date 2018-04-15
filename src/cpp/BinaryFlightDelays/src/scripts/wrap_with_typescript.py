from __future__ import print_function

from sys import argv

TEMPLATE_FILE = "wasm/CompactFlights.template.ts"


def wrap_with_typescript(path):
    filename, extension = path.split(".")
    if extension != "js":
        print("must compile from JS")
        return
    ts_path = filename + ".ts"
    ts_template = open(TEMPLATE_FILE).read()
    js = open(path).read()
    ts = ts_template.replace("let Module;", js)
    open(ts_path, "w").write(ts)


def main():
    if len(argv) != 2:
        print("no arguments")
        return
    path = argv[1]
    wrap_with_typescript(path)


if __name__ == '__main__':
    main()
