"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const class_1 = require("./class");
exports.CSSSelector = class_1.Class.new((function () {
    if (!document.styleSheets || !document.head) {
        throw new Error("CSSSelectors cannot be added dynamically");
    }
    const adaptCssRulesToRules = function (styleSheet) {
        styleSheet.rules = styleSheet.cssRules;
        styleSheet.addRule = function (selector, style, index) {
            return styleSheet.insertRule(selector + "{" + style + "}", styleSheet.rules.length);
        };
    };
    const getStyleSheet = function () {
        document.head.appendNewElement("style");
        const styleSheets = document.styleSheets;
        const styleSheet = styleSheets[styleSheets.length - 1];
        const mediaType = typeof styleSheet.media;
        if (mediaType === "object") {
            adaptCssRulesToRules(styleSheet);
        }
        return styleSheet;
    };
    const styleSheet = getStyleSheet();
    const rules = styleSheet.rules;
    return function (selector) {
        const selectorLowerCase = selector.toLowerCase();
        const addSelector = function (style) {
            for (const rule of rules) {
                if (rule.selectorText && selectorLowerCase === rule.selectorText.toLowerCase()) {
                    rule.style.cssText += style;
                    return;
                }
            }
            styleSheet.addRule(selector, style);
        };
        const lines = [];
        return {
            style(line) {
                lines.push(line);
                return this;
            },
            styles(styleObj) {
                for (const field in styleObj) {
                    if (styleObj.hasOwnProperty(field) && styleObj[field]) {
                        lines.push(field.replace("_", "-") + ": " + styleObj[field]);
                    }
                }
                return this;
            },
            create() {
                const style = lines.join(";");
                addSelector(style);
            },
        }.freeze();
    };
})());
//# sourceMappingURL=cssSelector.js.map