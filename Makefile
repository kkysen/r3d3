install:
	cd src/python; make install

install-compile:
	npm install

wasm:
	cd src/cpp/BinaryFlightDelays; make wasm

js:
	npm run watch

run:
	cd src/python; make run