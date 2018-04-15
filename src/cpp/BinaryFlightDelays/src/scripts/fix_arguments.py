from __future__ import print_function

from sys import argv


def fix_arguments(path):
    js = open(path).read()
    js = js.replace("args = args || Module['arguments'];", "")
    open(path, "w").write(js)


def main():
    if len(argv) != 2:
        print("no arguments")
        return
    path = argv[1]
    fix_arguments(path)


if __name__ == '__main__':
    main()
