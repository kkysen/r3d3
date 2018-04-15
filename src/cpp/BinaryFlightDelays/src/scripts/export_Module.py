from __future__ import print_function

from sys import argv


# noinspection PyPep8Naming
def export_Module(path):
    js = open(path).read()
    js = js.replace("var Module", "var Module = window.Module")
    open(path, "w").write(js)


def main():
    if len(argv) != 2:
        print("no arguments")
        return
    path = argv[1]
    export_Module(path)


if __name__ == '__main__':
    main()
