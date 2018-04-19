from __future__ import print_function

from sys import argv


def preprocess(path):
    js = open(path).read()
    js = js.replace("args = args || Module['arguments'];", "")
    js = js.replace('args=args||Module["arguments"];', "")
    js = js.replace("var Module", "var Module=window.Module")
    # js = js.replace("var invokerArgsArray", "console.log(humanName);\nvar invokerArgsArray")
    # js = js.replace("var memberFunction", "console.log(humanName);\nvar memberFunction")
    open(path, "w").write(js)


def main():
    if len(argv) != 2:
        print("no arguments")
        return
    path = argv[1]
    preprocess(path)


if __name__ == '__main__':
    main()
