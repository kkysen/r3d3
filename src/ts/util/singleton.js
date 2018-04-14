"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const class_1 = require("./class");
exports.Singleton = class_1.Class.new((constructor, ...args) => Object.freeze(constructor(...args)));
//# sourceMappingURL=singleton.js.map