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

/***/ "./src/ts/core/Flights.ts":
/*!********************************!*\
  !*** ./src/ts/core/Flights.ts ***!
  \********************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\r\nObject.defineProperty(exports, \"__esModule\", { value: true });\r\nconst wasm_1 = __webpack_require__(/*! ./wasm */ \"./src/ts/core/wasm.ts\");\r\nexports.flights = (function () {\r\n    const asUint8Array = function (response) {\r\n        return response.arrayBuffer()\r\n            .then(buffer => new Uint8Array(buffer));\r\n    };\r\n    const loadFlights = function (flights, airports, airlines) {\r\n        return wasm_1.Module.Flights.create(flights, airports, airlines);\r\n    };\r\n    const baseUrl = \"/data/\";\r\n    const create = function () {\r\n        return new Promise(resolve => {\r\n            fetch(baseUrl + \"airlines.csv\")\r\n                .catch(console.log)\r\n                .then(asUint8Array)\r\n                .then(airlines => {\r\n                fetch(baseUrl + \"airports.csv\")\r\n                    .catch(console.log)\r\n                    .then(asUint8Array)\r\n                    .then(airports => {\r\n                    fetch(baseUrl + \"flights.bin\")\r\n                        .catch(console.log)\r\n                        .then(asUint8Array)\r\n                        .then(flights => {\r\n                        resolve(loadFlights(flights, airports, airlines));\r\n                    });\r\n                });\r\n            });\r\n        });\r\n    };\r\n    let promise;\r\n    return {\r\n        get() {\r\n            return promise || (promise = create());\r\n        }\r\n    };\r\n})();\r\n\n\n//# sourceURL=webpack:///./src/ts/core/Flights.ts?");

/***/ }),

/***/ "./src/ts/core/wasm.ts":
/*!*****************************!*\
  !*** ./src/ts/core/wasm.ts ***!
  \*****************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\r\nObject.defineProperty(exports, \"__esModule\", { value: true });\r\nexports.Module.Flights.create = function (flightsData, airportsData, airlinesData) {\r\n    return exports.Module.Flights.jsCreate(flightsData, flightsData.length, airportsData, airportsData.length, airlinesData, airlinesData.length);\r\n};\r\n\n\n//# sourceURL=webpack:///./src/ts/core/wasm.ts?");

/***/ }),

/***/ "./src/ts/main.js":
/*!************************!*\
  !*** ./src/ts/main.js ***!
  \************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\r\nObject.defineProperty(exports, \"__esModule\", {value: true});\r\n__webpack_require__(/*! ./util/extensions */ \"./src/ts/util/extensions.ts\");\r\nconst r3d3_1 = __webpack_require__(/*! ./r3d3 */ \"./src/ts/r3d3.ts\");\r\n(function r3d3() {\r\n    r3d3_1.main();\r\n})();\r\n//# sourceMappingURL=main.js.map\n\n//# sourceURL=webpack:///./src/ts/main.js?");

/***/ }),

/***/ "./src/ts/r3d3.ts":
/*!************************!*\
  !*** ./src/ts/r3d3.ts ***!
  \************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
eval("\r\nObject.defineProperty(exports, \"__esModule\", { value: true });\r\nconst Flights_1 = __webpack_require__(/*! ./core/Flights */ \"./src/ts/core/Flights.ts\");\r\nexports.main = function () {\r\n    console.log(exports.main);\r\n    Flights_1.flights.get()\r\n        .then(flights => {\r\n        console.log(flights);\r\n    });\r\n};\r\n\n\n//# sourceURL=webpack:///./src/ts/r3d3.ts?");

/***/ }),

/***/ "./src/ts/util/extensions.ts":
/*!***********************************!*\
  !*** ./src/ts/util/extensions.ts ***!
  \***********************************/
/*! no static exports found */
/***/ (function(module, exports) {

eval("const immutableDescriptor = {\r\n    writable: false,\r\n    enumerable: false,\r\n    configurable: false,\r\n};\r\nconst defineSharedProperties = function (obj, sharedDescriptor, propertyValues) {\r\n    const properties = {};\r\n    for (const value in propertyValues) {\r\n        if (propertyValues.hasOwnProperty(value)) {\r\n            properties[value] = Object.assign({ value: propertyValues[value] }, sharedDescriptor);\r\n        }\r\n    }\r\n    Object.defineProperties(obj, properties);\r\n};\r\nconst defineImmutableProperties = function (obj, propertyValues) {\r\n    defineSharedProperties(obj, immutableDescriptor, propertyValues);\r\n};\r\nObject.defineProperties(Object, {\r\n    defineSharedProperties: {\r\n        writable: false,\r\n        enumerable: false,\r\n        configurable: false,\r\n        value: defineSharedProperties,\r\n    },\r\n    defineImmutableProperties: {\r\n        writable: false,\r\n        enumerable: false,\r\n        configurable: false,\r\n        value: defineImmutableProperties,\r\n    },\r\n});\r\nObject.defineImmutableProperties(Object, {\r\n    getting(key) {\r\n        return o => o[key];\r\n    },\r\n    deleting(key) {\r\n        return o => {\r\n            delete o[key];\r\n            return o;\r\n        };\r\n    },\r\n});\r\nObject.defineImmutableProperties(Object.prototype, {\r\n    freeze() {\r\n        return Object.freeze(this);\r\n    },\r\n    seal() {\r\n        return Object.seal(this);\r\n    },\r\n    _clone() {\r\n        return Object.assign({}, this);\r\n    },\r\n});\r\nObject.defineImmutableProperties(Function, {\r\n    compose(...funcs) {\r\n        const numFuncs = funcs.length;\r\n        if (numFuncs === 0) {\r\n            return () => undefined;\r\n        }\r\n        if (numFuncs === 1) {\r\n            return funcs[0];\r\n        }\r\n        return function (...args) {\r\n            let result = funcs[0](...args);\r\n            for (let i = 1; i < numFuncs; i++) {\r\n                result = funcs[i](result);\r\n            }\r\n            return result;\r\n        };\r\n    },\r\n});\r\nObject.defineImmutableProperties(Function.prototype, {\r\n    then(nextFunc) {\r\n        return (arg) => nextFunc(this(arg));\r\n    },\r\n    applyReturning() {\r\n        return (arg) => {\r\n            this(arg);\r\n            return arg;\r\n        };\r\n    },\r\n});\r\nObject.defineImmutableProperties(Array.prototype, {\r\n    clear() {\r\n        this.length = 0;\r\n    },\r\n    remove(value) {\r\n        const i = this.indexOf(value);\r\n        if (i !== -1) {\r\n            this.splice(i, 1);\r\n        }\r\n    },\r\n});\r\nObject.defineImmutableProperties(Number, {\r\n    isNumber(n) {\r\n        return !Number.isNaN(n);\r\n    },\r\n    toPixels(n) {\r\n        return n + \"px\";\r\n    },\r\n});\r\nObject.defineImmutableProperties(Node.prototype, {\r\n    appendBefore(node) {\r\n        return this.parentNode.insertBefore(node, this);\r\n    },\r\n    appendAfter(node) {\r\n        return this.nextSibling.appendBefore(node);\r\n    },\r\n});\r\nObject.defineImmutableProperties(Element.prototype, {\r\n    clearHTML() {\r\n        this.innerHTML = \"\";\r\n    },\r\n    setAttributes(attributes) {\r\n        for (const attribute in attributes) {\r\n            if (attributes.hasOwnProperty(attribute) && attributes[attribute]) {\r\n                this.setAttribute(attribute, attributes[attribute].toString());\r\n            }\r\n        }\r\n    },\r\n});\r\nObject.defineImmutableProperties(HTMLElement.prototype, {\r\n    appendNewElement(tagName) {\r\n        return this.appendChild(document.createElement(tagName));\r\n    },\r\n    appendDiv() {\r\n        return this.appendNewElement(\"div\");\r\n    },\r\n    appendButton(buttonText) {\r\n        const button = this.appendNewElement(\"button\");\r\n        button.innerText = buttonText;\r\n        return button;\r\n    },\r\n    appendBr() {\r\n        return this.appendNewElement(\"br\");\r\n    },\r\n    withInnerText(text) {\r\n        this.innerText = text;\r\n        return this;\r\n    },\r\n});\r\n\n\n//# sourceURL=webpack:///./src/ts/util/extensions.ts?");

/***/ })

/******/ });