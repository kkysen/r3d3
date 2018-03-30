import {Class} from "./class";

export const Singleton = Class.new((constructor, ...args) => Object.freeze(constructor(...args)));