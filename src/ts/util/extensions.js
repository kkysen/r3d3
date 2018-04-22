const immutableDescriptor = {
    writable: false,
    enumerable: false,
    configurable: false,
};
const defineSharedProperties = function (obj, sharedDescriptor, propertyValues) {
    const properties = Object.getOwnPropertyDescriptors(propertyValues);
    for (const propertyName in properties) {
        if (properties.hasOwnProperty(propertyName)) {
            let property = properties[propertyName];
            property = Object.assign(property, sharedDescriptor);
            if (property.get || property.set) {
                delete property.writable;
            }
            properties[propertyName] = property;
        }
    }
    Object.defineProperties(obj, properties);
};
const defineImmutableProperties = function (obj, propertyValues) {
    defineSharedProperties(obj, immutableDescriptor, propertyValues);
};
Object.defineProperties(Object, {
    defineSharedProperties: {
        writable: false,
        enumerable: false,
        configurable: false,
        value: defineSharedProperties,
    },
    defineImmutableProperties: {
        writable: false,
        enumerable: false,
        configurable: false,
        value: defineImmutableProperties,
    },
});
Object.defineImmutableProperties(Object, {
    getting(key) {
        return o => o[key];
    },
    deleting(key) {
        return o => {
            delete o[key];
            return o;
        };
    },
});
Object.defineImmutableProperties(Object.prototype, {
    freeze() {
        return Object.freeze(this);
    },
    seal() {
        return Object.seal(this);
    },
    _clone() {
        return Object.assign({}, this);
    },
});
Object.defineImmutableProperties(Function, {
    compose(...funcs) {
        const numFuncs = funcs.length;
        if (numFuncs === 0) {
            return () => undefined;
        }
        if (numFuncs === 1) {
            return funcs[0];
        }
        return function (...args) {
            let result = funcs[0](...args);
            for (let i = 1; i < numFuncs; i++) {
                result = funcs[i](result);
            }
            return result;
        };
    },
});
Object.defineImmutableProperties(Function.prototype, {
    then(nextFunc) {
        return (arg) => nextFunc(this(arg));
    },
    applyReturning() {
        return (arg) => {
            this(arg);
            return arg;
        };
    },
    mapping() {
        return array => array.map(this);
    },
    applying() {
        return array => this(...array);
    },
    timed() {
        const timer = (...args) => {
            console.time(this.name);
            const returnValue = this(...args);
            console.timeEnd(this.name);
            return returnValue;
        };
        timer.name = "timing_" + this.name;
        return timer;
    },
});
Object.defineImmutableProperties(Array.prototype, {
    clear() {
        this.length = 0;
    },
    remove(value) {
        const i = this.indexOf(value);
        if (i !== -1) {
            this.splice(i, 1);
        }
    },
    applyOn(func) {
        return func(this);
    },
    callOn(func) {
        return func(...this);
    },
    toObject() {
        let o = {};
        for (const [k, v] of this) {
            o[k] = v;
        }
        return o;
    },
});
Object.defineImmutableProperties(Number, {
    isNumber(n) {
        return !Number.isNaN(n);
    },
    toPixels(n) {
        return n + "px";
    },
});
Object.defineImmutableProperties(Node.prototype, {
    appendBefore(node) {
        return this.parentNode.insertBefore(node, this);
    },
    appendAfter(node) {
        return this.nextSibling.appendBefore(node);
    },
});
Object.defineImmutableProperties(Element.prototype, {
    clearHTML() {
        this.innerHTML = "";
    },
    setAttributes(attributes) {
        for (const attribute in attributes) {
            if (attributes.hasOwnProperty(attribute) && attributes[attribute]) {
                this.setAttribute(attribute, attributes[attribute].toString());
            }
        }
    },
});
Object.defineImmutableProperties(HTMLElement.prototype, {
    appendNewElement(tagName) {
        return this.appendChild(document.createElement(tagName));
    },
    appendDiv() {
        return this.appendNewElement("div");
    },
    appendButton(buttonText) {
        const button = this.appendNewElement("button");
        button.innerText = buttonText;
        return button;
    },
    appendBr() {
        return this.appendNewElement("br");
    },
    withInnerText(text) {
        this.innerText = text;
        return this;
    },
});
//# sourceMappingURL=extensions.js.map