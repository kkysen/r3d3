declare interface HTMLAppendable<T> {

    appendTo(parent: HTMLElement): T;

}

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
    const properties: PropertyDescriptorMap & ThisType<any> = Object.getOwnPropertyDescriptors(propertyValues);
    for (const propertyName in properties) {
        if (properties.hasOwnProperty(propertyName)) {
            let property: PropertyDescriptor = properties[propertyName];
            property = Object.assign(property, sharedDescriptor);
            if (property.get || property.set) {
                delete property.writable;
            }
            properties[propertyName] = property;
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
    
    then<T, U, V>(this: (arg: T) => U, nextFunc: (arg: U) => V): (arg: T) => V;
    
    applyReturning<T>(this: (arg: T) => void): (arg: T) => T;
    
    mapping<T, U>(this: (arg: T) => U): (array: T[]) => U[];
    
    applying<T, U>(this: (...args: T[]) => U): (array: T[]) => U;
    
    timed<T>(this: T): T;
    
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
    
    mapping<T, U>(this: (arg: T) => U): (array: T[]) => U[] {
        return array => array.map(this);
    },
    
    applying<T, U>(this: (...args: T[]) => U): (array: T[]) => U {
        return array => this(...array);
    },
    
    timed<T extends Function>(this: T): T {
        const timer = (...args) => {
            console.time(this.name);
            const returnValue = this(...args);
            console.timeEnd(this.name);
            return returnValue;
        };
        (<any> timer).name = "timing_" + this.name;
        return <T> <any> timer;
    },
    
});

declare interface Array<T> {
    
    clear(): void;
    
    remove(value: T): void;
    
    applyOn<T, U>(this: T[], func: (args: T[]) => U): U;
    
    callOn<T, U>(this: T[], func: (...args: T[]) => U): U;
    
    toObject<T>(this: [string, T][]): {[property: string]: T};
    
    toObject(this: [string, any][]): any;
    
    sortBy<T, U>(this: T[], key: (t: T) => U): T[];
    
    random<T>(this: T[]): T;
    
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
    
    applyOn<T, U>(this: T[], func: (args: T[]) => U): U {
        return func(this);
    },
    
    callOn<T, U>(this: T[], func: (...args: T[]) => U): U {
        return func(...this);
    },
    
    toObject(this: [string, any][]): any {
        let o = {};
        for (const [k, v] of this) {
            o[k] = v;
        }
        return o;
    },
    
    sortBy<T, U extends number>(this: T[], key: (t: T) => U): T[] {
        this.sort((a, b) => key(a) - key(b));
        return this;
    },
    
    random<T>(this: T[]): T {
        return this[Math.floor(Math.random() * this.length)];
    },
    
});

declare interface NumberConstructor {
    
    isNumber(n: number): boolean;
    
    toPixels(n: number): string;
    
}

Object.defineImmutableProperties(Number, {
    
    isNumber(n: number): boolean {
        return !Number.isNaN(n);
    },
    
    toPixels(n: number): string {
        return Math.round(n) + "px";
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
    
    appendTo<T extends HTMLElement>(this: T, parent: HTMLElement): T;
    
    appendNewElement<K extends keyof HTMLElementTagNameMap>(tagName: K): HTMLElementTagNameMap[K];
    
    appendNewElement(tagName: string): HTMLElement;
    
    appendDiv(): HTMLDivElement;
    
    appendButton(buttonText: string): HTMLButtonElement;
    
    appendBr(): HTMLBRElement;
    
    withInnerText<T extends HTMLElement>(this: T, text: string): T;
    
    withInnerHTML<T extends HTMLElement>(this: T, html: string): T;
    
}

declare interface HTMLElement extends HTMLAppendable<HTMLElement> {}

Object.defineImmutableProperties(HTMLElement.prototype, {
    
    appendTo<T extends HTMLElement>(this: T, parent: HTMLElement): T {
        parent.appendChild(this);
        return this;
    },
    
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
    
    withInnerText<T extends HTMLElement>(this: T, text: string): T {
        this.innerText = text;
        return this;
    },
    
    withInnerHTML<T extends HTMLElement>(this: T, html: string): T {
        this.innerHTML = html;
        return this;
    },
    
});