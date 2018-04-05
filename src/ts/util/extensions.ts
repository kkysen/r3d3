declare interface ObjectConstructor {
    
    defineSharedProperties(object: any, sharedDescriptor: PropertyDescriptor, propertyValues: Object);
    
    defineImmutableProperties(object: any, propertyValues: Object);
    
    getting<T, K extends keyof T>(key: K): (o: T) => T[K];
    
    deleting<T, K extends keyof T>(key: K): (o: T) => T;
    
}

const immutableDescriptor: PropertyDescriptor = {
    writable: false,
    enumerable: false,
    configurable: false,
};

const defineSharedProperties = function(obj: any, sharedDescriptor: PropertyDescriptor, propertyValues: Object) {
    const properties: PropertyDescriptorMap & ThisType<any> = {};
    for (const value in propertyValues) {
        if (propertyValues.hasOwnProperty(value)) {
            properties[value] = Object.assign({value: propertyValues[value]}, sharedDescriptor);
        }
    }
    Object.defineProperties(obj, properties);
};

const defineImmutableProperties = function(obj: any, propertyValues: Object) {
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
    
    getting<T, K extends keyof T>(key: K): (o: T) => T[K] {
        return o => o[key];
    },
    
    deleting<T, K extends keyof T>(key: K): (o: T) => T {
        return o => {
            delete o[key];
            return o;
        };
    },
    
});

declare interface Object {
    
    freeze<T>(this: T): T;
    
    seal<T>(this: T): T;
    
    // _ is b/c there are other objects with slightly different clone methods
    _clone<T>(this: T): T;
    
}

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

declare interface FunctionConstructor {
    
    compose(...funcs: Function[]): Function;
    
}

Object.defineImmutableProperties(Function, {
    
    compose(...funcs: Function[]): Function {
        const numFuncs: number = funcs.length;
        if (numFuncs === 0) {
            return () => undefined;
        }
        if (numFuncs === 1) {
            return funcs[0];
        }
        return function(...args) {
            let result = funcs[0](...args);
            for (let i = 1; i < numFuncs; i++) {
                result = funcs[i](result);
            }
            return result;
        };
    },
    
});

declare interface Function {
    
    then<T, U, V>(this: (arg: T) => T, nextFunc: (arg: U) => V): (arg: T) => V;
    
    applyReturning<T>(this: (arg: T) => void): (arg: T) => T;
    
}

Object.defineImmutableProperties(Function.prototype, {
    
    then<T, U, V>(this: (arg: T) => U, nextFunc: (arg: U) => V): (arg: T) => V {
        return (arg: T) => nextFunc(this(arg));
    },
    
    applyReturning<T>(this: (arg: T) => void): (arg: T) => T {
        return (arg: T) => {
            this(arg);
            return arg;
        };
    },
    
});

declare interface Array<T> {
    
    clear(): void;
    
    remove(value: T): void;
    
}

Object.defineImmutableProperties(Array.prototype, {
    
    clear(): void {
        this.length = 0;
    },
    
    remove<T>(this: T[], value: T): void {
        const i: number = this.indexOf(value);
        if (i !== -1) {
            this.splice(i, 1);
        }
    },
    
});

declare interface NumberConstructor {
    
    isNumber(n: any): boolean;
    
    toPixels(n: number): string;
    
}

Object.defineImmutableProperties(Number, {
    
    isNumber(n: number): boolean {
        return !Number.isNaN(n);
    },
    
    toPixels(n: number): string {
        return n + "px";
    },
    
});

declare interface Node {

    appendBefore(node: Node): Node;
    
    appendAfter(node: Node): Node;

}

Object.defineImmutableProperties(Node.prototype, {
    
    appendBefore(this: Node, node: Node): Node {
        return this.parentNode.insertBefore(node, this);
    },
    
    appendAfter(this: Node, node: Node): Node {
        return this.nextSibling.appendBefore(node);
    },
    
});

declare interface Element {
    
    clearHTML(): void;
    
    setAttributes(attributes: {[name: string]: any}): void;
    
}

Object.defineImmutableProperties(Element.prototype, {
    
    clearHTML() {
        this.innerHTML = "";
    },
    
    setAttributes(attributes: {[name: string]: any}) {
        for (const attribute in attributes) {
            if (attributes.hasOwnProperty(attribute) && attributes[attribute]) {
                this.setAttribute(attribute, attributes[attribute].toString());
            }
        }
    },
    
});

declare interface HTMLElement {
    
    appendNewElement<K extends keyof HTMLElementTagNameMap>(tagName: K): HTMLElementTagNameMap[K];
    
    appendNewElement(tagName: string): HTMLElement;
    
    appendDiv(): HTMLDivElement;
    
    appendButton(buttonText: string): HTMLButtonElement;
    
    appendBr(): HTMLBRElement;
    
    withInnerText(text: string): HTMLElement;
    
}

Object.defineImmutableProperties(HTMLElement.prototype, {
    
    appendNewElement(tagName: string): HTMLElement {
        return this.appendChild(document.createElement(tagName));
    },
    
    appendDiv(): HTMLDivElement {
        return this.appendNewElement("div");
    },
    
    appendButton(buttonText: string): HTMLButtonElement {
        const button = this.appendNewElement("button");
        button.innerText = buttonText;
        return button;
    },
    
    appendBr(): HTMLBRElement {
        return this.appendNewElement("br");
    },
    
    withInnerText(text: string): HTMLElement {
        this.innerText = text;
        return this;
    },
    
});