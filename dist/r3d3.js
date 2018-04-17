/******/ (function(modules) { // webpackBootstrap
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId]) {
/******/ 			return installedModules[moduleId].exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			i: moduleId,
/******/ 			l: false,
/******/ 			exports: {}
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.l = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// define getter function for harmony exports
/******/ 	__webpack_require__.d = function(exports, name, getter) {
/******/ 		if(!__webpack_require__.o(exports, name)) {
/******/ 			Object.defineProperty(exports, name, {
/******/ 				configurable: false,
/******/ 				enumerable: true,
/******/ 				get: getter
/******/ 			});
/******/ 		}
/******/ 	};
/******/
/******/ 	// define __esModule on exports
/******/ 	__webpack_require__.r = function(exports) {
/******/ 		Object.defineProperty(exports, '__esModule', { value: true });
/******/ 	};
/******/
/******/ 	// getDefaultExport function for compatibility with non-harmony modules
/******/ 	__webpack_require__.n = function(module) {
/******/ 		var getter = module && module.__esModule ?
/******/ 			function getDefault() { return module['default']; } :
/******/ 			function getModuleExports() { return module; };
/******/ 		__webpack_require__.d(getter, 'a', getter);
/******/ 		return getter;
/******/ 	};
/******/
/******/ 	// Object.prototype.hasOwnProperty.call
/******/ 	__webpack_require__.o = function(object, property) { return Object.prototype.hasOwnProperty.call(object, property); };
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "";
/******/
/******/
/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(__webpack_require__.s = "./src/ts/main.js");
/******/ })
/************************************************************************/
/******/ ({

/***/ "./src/ts/core/DynamicEnum.ts":
/*!************************************!*\
  !*** ./src/ts/core/DynamicEnum.ts ***!
  \************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\r\nObject.defineProperty(exports, \"__esModule\", { value: true });\r\nconst range_1 = __webpack_require__(/*! ../util/range */ \"./src/ts/util/range.ts\");\r\nexports.DynamicEnum = {\r\n    addAllFunction(dynamicEnum, alias) {\r\n        dynamicEnum.all = function () {\r\n            return range_1.Range.new(dynamicEnum.count())\r\n                .map(i => dynamicEnum.of(i));\r\n        };\r\n        if (alias) {\r\n            dynamicEnum[alias] = dynamicEnum.all;\r\n        }\r\n    },\r\n};\r\n\n\n//# sourceURL=webpack:///./src/ts/core/DynamicEnum.ts?");

/***/ }),

/***/ "./src/ts/core/Flights.ts":
/*!********************************!*\
  !*** ./src/ts/core/Flights.ts ***!
  \********************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\r\nObject.defineProperty(exports, \"__esModule\", { value: true });\r\nconst cachedFetch_1 = __webpack_require__(/*! ../util/cachedFetch */ \"./src/ts/util/cachedFetch.ts\");\r\nconst wasm_1 = __webpack_require__(/*! ./wasm */ \"./src/ts/core/wasm.ts\");\r\nexports.flightsPromise = (function () {\r\n    const hex = function (buffer) {\r\n        const hexCodes = [];\r\n        const view = new DataView(buffer);\r\n        for (let i = 0; i < view.byteLength; i += 4) {\r\n            // Using getUint32 reduces the number of iterations needed (we process 4 bytes each time)\r\n            const value = view.getUint32(i);\r\n            // toString(16) will give the hex representation of the number without padding\r\n            const stringValue = value.toString(16);\r\n            // We use concatenation and slice for padding\r\n            const padding = \"00000000\";\r\n            const paddedValue = (padding + stringValue).slice(-padding.length);\r\n            hexCodes.push(paddedValue);\r\n        }\r\n        // Join all the hex strings into one\r\n        return hexCodes.join(\"\");\r\n    };\r\n    let i = 0;\r\n    const asUint8Array = async function (response) {\r\n        console.log(response);\r\n        const j = ++i;\r\n        const buffer = new Uint8Array(await response.arrayBuffer());\r\n        // SHA._256.hash(buffer).then(hash => console.log(j, hash));\r\n        return buffer;\r\n    };\r\n    const loadFlights = function (_flights, airports, airlines) {\r\n        return exports.flights = window.flights = wasm_1.Module.Flights.create(_flights, airports, airlines);\r\n    };\r\n    const create = function () {\r\n        Promise.all = Promise.all.bind(Promise);\r\n        return [\"flights.bin\", \"airports.csv\", \"airlines.csv\"]\r\n            .map(name => \"data/\" + name)\r\n            .map(url => cachedFetch_1.cachedFetch(url))\r\n            .applyOn(Promise.all)\r\n            .then(asUint8Array.mapping())\r\n            .then(Promise.all)\r\n            .then(loadFlights.applying());\r\n    };\r\n    let promise;\r\n    return {\r\n        get() {\r\n            return promise || (promise = create());\r\n        }\r\n    };\r\n})();\r\n\n\n//# sourceURL=webpack:///./src/ts/core/Flights.ts?");

/***/ }),

/***/ "./src/ts/core/GetArray.ts":
/*!*********************************!*\
  !*** ./src/ts/core/GetArray.ts ***!
  \*********************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\r\nObject.defineProperty(exports, \"__esModule\", { value: true });\r\nconst range_1 = __webpack_require__(/*! ../util/range */ \"./src/ts/util/range.ts\");\r\nexports.GetArray = {\r\n    addToArrayFunction(getArray) {\r\n        const prototype = Object.getPrototypeOf(getArray);\r\n        if (prototype.toArray) {\r\n            return;\r\n        }\r\n        prototype.toArray = function () {\r\n            return range_1.Range.new(this.size())\r\n                .map(i => this.get(i));\r\n        };\r\n    },\r\n};\r\n\n\n//# sourceURL=webpack:///./src/ts/core/GetArray.ts?");

/***/ }),

/***/ "./src/ts/core/wasm.ts":
/*!*****************************!*\
  !*** ./src/ts/core/wasm.ts ***!
  \*****************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\r\nObject.defineProperty(exports, \"__esModule\", { value: true });\r\nconst DynamicEnum_1 = __webpack_require__(/*! ./DynamicEnum */ \"./src/ts/core/DynamicEnum.ts\");\r\nconst Flights_1 = __webpack_require__(/*! ./Flights */ \"./src/ts/core/Flights.ts\");\r\nconst GetArray_1 = __webpack_require__(/*! ./GetArray */ \"./src/ts/core/GetArray.ts\");\r\nexports.Module = undefined;\r\nexports.runAfterWasm = function (func) {\r\n    // console.log(func);\r\n    exports.Module = exports.Module || window.Module;\r\n    return new Promise(resolve => {\r\n        const wrapper = function () {\r\n            resolve(func());\r\n        };\r\n        if (exports.Module.Flights) {\r\n            wrapper();\r\n        }\r\n        else {\r\n            exports.Module.postRun.push(wrapper);\r\n        }\r\n    });\r\n};\r\nconst extendInterfaces = function (Module) {\r\n    Module.Flights.create = function (flightsData, airportsData, airlinesData) {\r\n        console.log(\"create\", arguments);\r\n        return Module.Flights.jsCreate(flightsData, airportsData, airlinesData);\r\n    };\r\n    DynamicEnum_1.DynamicEnum.addAllFunction(Module.Airport, \"airports\");\r\n    DynamicEnum_1.DynamicEnum.addAllFunction(Module.Airline, \"airlines\");\r\n};\r\nexports.extendFlightsInterfaces = function () {\r\n    GetArray_1.GetArray.addToArrayFunction(Flights_1.flights);\r\n    GetArray_1.GetArray.addToArrayFunction(Flights_1.flights.get(0));\r\n};\r\nexports.postWasm = function () {\r\n    console.log(\"postWasm\");\r\n    extendInterfaces(exports.Module);\r\n};\r\n\n\n//# sourceURL=webpack:///./src/ts/core/wasm.ts?");

/***/ }),

/***/ "./src/ts/main.js":
/*!************************!*\
  !*** ./src/ts/main.js ***!
  \************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\r\nObject.defineProperty(exports, \"__esModule\", { value: true });\r\n__webpack_require__(/*! ./util/extensions */ \"./src/ts/util/extensions.ts\");\r\nconst r3d3_1 = __webpack_require__(/*! ./r3d3 */ \"./src/ts/r3d3.ts\");\r\n(function r3d3() {\r\n    r3d3_1.main();\r\n})();\r\n//# sourceMappingURL=main.js.map\n\n//# sourceURL=webpack:///./src/ts/main.js?");

/***/ }),

/***/ "./src/ts/r3d3.ts":
/*!************************!*\
  !*** ./src/ts/r3d3.ts ***!
  \************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\r\nObject.defineProperty(exports, \"__esModule\", { value: true });\r\nconst Flights_1 = __webpack_require__(/*! ./core/Flights */ \"./src/ts/core/Flights.ts\");\r\nconst wasm_1 = __webpack_require__(/*! ./core/wasm */ \"./src/ts/core/wasm.ts\");\r\nconst timeDistances = window.timeDistances = function () {\r\n    console.log(\"running\");\r\n    // let distance: number = 0;\r\n    // for (let i = 0; i < flights.size(); i++) {\r\n    //     console.log(i, distance);\r\n    //     const flightsInDay = flights.get(i);\r\n    //     for (let j = 0; j < flightsInDay.size(); j++) {\r\n    //         distance += flightsInDay.get(j).distance();\r\n    //     }\r\n    // }\r\n    console.log(Flights_1.flights.totalDistance());\r\n};\r\nconst flightsMain = function () {\r\n    // const flightsInDay = flightsPromise.flightsInDay(1);\r\n    // console.log(flightsInDay);\r\n    const flight = Flights_1.flights.flight(0, 0);\r\n    console.log(flight);\r\n    console.log(flight.departure());\r\n    console.log(flight.departure().airport());\r\n    console.log(flight.departure().airport().name());\r\n    timeDistances.timed()();\r\n};\r\nconst preFlightsMain = function () {\r\n};\r\nconst realMain = function () {\r\n    console.log(\"realMain\");\r\n    preFlightsMain();\r\n    Flights_1.flightsPromise.get()\r\n        .then(flights => {\r\n        console.log(flights);\r\n        // global flights will have loaded now\r\n        wasm_1.extendFlightsInterfaces();\r\n        flightsMain();\r\n    });\r\n};\r\nexports.main = function () {\r\n    [wasm_1.postWasm, realMain].forEach(wasm_1.runAfterWasm);\r\n};\r\n\n\n//# sourceURL=webpack:///./src/ts/r3d3.ts?");

/***/ }),

/***/ "./src/ts/util/cachedFetch.ts":
/*!************************************!*\
  !*** ./src/ts/util/cachedFetch.ts ***!
  \************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\r\nObject.defineProperty(exports, \"__esModule\", { value: true });\r\nconst deserializeResponse = function (serialized) {\r\n    return new Response(new TextEncoder().encode(serialized));\r\n};\r\nconst serializeResponse = function (arrayBuffer) {\r\n    return new TextDecoder().decode(arrayBuffer);\r\n};\r\nexports.cachedFetch = function (input, init) {\r\n    const key = JSON.stringify({\r\n        input: input,\r\n        init: init,\r\n    });\r\n    const cachedValue = localStorage.getItem(key);\r\n    if (cachedValue) {\r\n        return Promise.resolve(deserializeResponse(cachedValue));\r\n    }\r\n    init = init || {};\r\n    init.cache = \"reload\"; // force reload, b/c caching anyways\r\n    return fetch(input, init)\r\n        .then(response => response.arrayBuffer())\r\n        .then(buffer => {\r\n        try {\r\n            localStorage.setItem(key, serializeResponse(buffer));\r\n        }\r\n        catch (e) {\r\n            console.log(\"unable to cache in localStorage\");\r\n            console.log(e);\r\n        }\r\n        return new Response(buffer);\r\n    });\r\n};\r\n\n\n//# sourceURL=webpack:///./src/ts/util/cachedFetch.ts?");

/***/ }),

/***/ "./src/ts/util/extensions.ts":
/*!***********************************!*\
  !*** ./src/ts/util/extensions.ts ***!
  \***********************************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("const immutableDescriptor = {\r\n    writable: false,\r\n    enumerable: false,\r\n    configurable: false,\r\n};\r\nconst defineSharedProperties = function (obj, sharedDescriptor, propertyValues) {\r\n    const properties = {};\r\n    for (const value in propertyValues) {\r\n        if (propertyValues.hasOwnProperty(value)) {\r\n            properties[value] = Object.assign({ value: propertyValues[value] }, sharedDescriptor);\r\n        }\r\n    }\r\n    Object.defineProperties(obj, properties);\r\n};\r\nconst defineImmutableProperties = function (obj, propertyValues) {\r\n    defineSharedProperties(obj, immutableDescriptor, propertyValues);\r\n};\r\nObject.defineProperties(Object, {\r\n    defineSharedProperties: {\r\n        writable: false,\r\n        enumerable: false,\r\n        configurable: false,\r\n        value: defineSharedProperties,\r\n    },\r\n    defineImmutableProperties: {\r\n        writable: false,\r\n        enumerable: false,\r\n        configurable: false,\r\n        value: defineImmutableProperties,\r\n    },\r\n});\r\nObject.defineImmutableProperties(Object, {\r\n    getting(key) {\r\n        return o => o[key];\r\n    },\r\n    deleting(key) {\r\n        return o => {\r\n            delete o[key];\r\n            return o;\r\n        };\r\n    },\r\n});\r\nObject.defineImmutableProperties(Object.prototype, {\r\n    freeze() {\r\n        return Object.freeze(this);\r\n    },\r\n    seal() {\r\n        return Object.seal(this);\r\n    },\r\n    _clone() {\r\n        return Object.assign({}, this);\r\n    },\r\n});\r\nObject.defineImmutableProperties(Function, {\r\n    compose(...funcs) {\r\n        const numFuncs = funcs.length;\r\n        if (numFuncs === 0) {\r\n            return () => undefined;\r\n        }\r\n        if (numFuncs === 1) {\r\n            return funcs[0];\r\n        }\r\n        return function (...args) {\r\n            let result = funcs[0](...args);\r\n            for (let i = 1; i < numFuncs; i++) {\r\n                result = funcs[i](result);\r\n            }\r\n            return result;\r\n        };\r\n    },\r\n});\r\nObject.defineImmutableProperties(Function.prototype, {\r\n    then(nextFunc) {\r\n        return (arg) => nextFunc(this(arg));\r\n    },\r\n    applyReturning() {\r\n        return (arg) => {\r\n            this(arg);\r\n            return arg;\r\n        };\r\n    },\r\n    mapping() {\r\n        return array => array.map(this);\r\n    },\r\n    applying() {\r\n        return array => this(...array);\r\n    },\r\n    timed() {\r\n        const timer = (...args) => {\r\n            console.time(this.name);\r\n            const returnValue = this(...args);\r\n            console.timeEnd(this.name);\r\n            return returnValue;\r\n        };\r\n        timer.name = \"timing_\" + this.name;\r\n        return timer;\r\n    },\r\n});\r\nObject.defineImmutableProperties(Array.prototype, {\r\n    clear() {\r\n        this.length = 0;\r\n    },\r\n    remove(value) {\r\n        const i = this.indexOf(value);\r\n        if (i !== -1) {\r\n            this.splice(i, 1);\r\n        }\r\n    },\r\n    applyOn(func) {\r\n        return func(this);\r\n    },\r\n    callOn(func) {\r\n        return func(...this);\r\n    },\r\n});\r\nObject.defineImmutableProperties(Number, {\r\n    isNumber(n) {\r\n        return !Number.isNaN(n);\r\n    },\r\n    toPixels(n) {\r\n        return n + \"px\";\r\n    },\r\n});\r\nObject.defineImmutableProperties(Node.prototype, {\r\n    appendBefore(node) {\r\n        return this.parentNode.insertBefore(node, this);\r\n    },\r\n    appendAfter(node) {\r\n        return this.nextSibling.appendBefore(node);\r\n    },\r\n});\r\nObject.defineImmutableProperties(Element.prototype, {\r\n    clearHTML() {\r\n        this.innerHTML = \"\";\r\n    },\r\n    setAttributes(attributes) {\r\n        for (const attribute in attributes) {\r\n            if (attributes.hasOwnProperty(attribute) && attributes[attribute]) {\r\n                this.setAttribute(attribute, attributes[attribute].toString());\r\n            }\r\n        }\r\n    },\r\n});\r\nObject.defineImmutableProperties(HTMLElement.prototype, {\r\n    appendNewElement(tagName) {\r\n        return this.appendChild(document.createElement(tagName));\r\n    },\r\n    appendDiv() {\r\n        return this.appendNewElement(\"div\");\r\n    },\r\n    appendButton(buttonText) {\r\n        const button = this.appendNewElement(\"button\");\r\n        button.innerText = buttonText;\r\n        return button;\r\n    },\r\n    appendBr() {\r\n        return this.appendNewElement(\"br\");\r\n    },\r\n    withInnerText(text) {\r\n        this.innerText = text;\r\n        return this;\r\n    },\r\n});\r\n\n\n//# sourceURL=webpack:///./src/ts/util/extensions.ts?");

/***/ }),

/***/ "./src/ts/util/range.ts":
/*!******************************!*\
  !*** ./src/ts/util/range.ts ***!
  \******************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\r\nObject.defineProperty(exports, \"__esModule\", { value: true });\r\nexports.Range = Object.freeze({\r\n    new(from, to) {\r\n        if (!to) {\r\n            to = from;\r\n            from = 0;\r\n        }\r\n        return {\r\n            map(func) {\r\n                const a = new Array(to - from);\r\n                for (let i = from; i < to; i++) {\r\n                    a[i - from] = func(i);\r\n                }\r\n                return a;\r\n            },\r\n            forEach(func) {\r\n                for (let i = from; i < to; i++) {\r\n                    func(i);\r\n                }\r\n            },\r\n            toArray() {\r\n                return this.map(i => i);\r\n            },\r\n            toInterval() {\r\n                return [from, to];\r\n            },\r\n        };\r\n    },\r\n    ofDomain(domain) {\r\n        return this.new(Math.min(...domain), Math.max(...domain));\r\n    },\r\n});\r\n\n\n//# sourceURL=webpack:///./src/ts/util/range.ts?");

/***/ })

/******/ });