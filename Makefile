install:
	cd src/python; make

install-compile:
	npm install

wasm:
	cd src/cpp/BinaryFlightDelays; make wasm

js:
	npm run watch

run:
	cd src/python; make