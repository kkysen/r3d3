import {Class} from "./class";

export interface CSSSelector {
    
    style(line: string): CSSSelector;
    
    styles(styleObj: Object): CSSSelector;
    
    create(): void;
    
}

export type CSSSelectorClass = {
    
    new(selector: string): CSSSelector,
    
};

export const CSSSelector: CSSSelectorClass = <CSSSelectorClass> <any> Class.new((function() {
    
    if (!document.styleSheets || !document.head) {
        throw new Error("CSSSelectors cannot be added dynamically");
    }
    
    const adaptCssRulesToRules = function(styleSheet: CSSStyleSheet): void {
        (<any> styleSheet).rules = styleSheet.cssRules;
        styleSheet.addRule = function(selector: string, style: string, index?: number): number {
            return styleSheet.insertRule(selector + "{" + style + "}", styleSheet.rules.length);
        };
    };
    
    const getStyleSheet = function(): CSSStyleSheet {
        document.head.appendNewElement("style");
        const styleSheets: StyleSheetList = document.styleSheets;
        const styleSheet: CSSStyleSheet = <CSSStyleSheet> styleSheets[styleSheets.length - 1];
        const mediaType: string = typeof styleSheet.media;
        if (mediaType === "object") {
            adaptCssRulesToRules(styleSheet);
        }
        return styleSheet;
    };
    
    const styleSheet: CSSStyleSheet = getStyleSheet();
    const rules: CSSStyleRule[] = <CSSStyleRule[]> <any> styleSheet.rules;
    
    return function(selector: string): CSSSelector {
        
        const selectorLowerCase: string = selector.toLowerCase();
        
        const addSelector = function(style: string) {
            for (const rule of rules) {
                if (rule.selectorText && selectorLowerCase === rule.selectorText.toLowerCase()) {
                    rule.style.cssText += style;
                    return;
                }
            }
            styleSheet.addRule(selector, style);
        };
        
        const lines: string[] = [];
        
        return {
            
            style(line: string): CSSSelector {
                lines.push(line);
                return this;
            },
            
            styles(styleObj: Object): CSSSelector {
                for (const field in styleObj) {
                    if (styleObj.hasOwnProperty(field) && styleObj[field]) {
                        lines.push(field.replace("_", "-") + ": " + styleObj[field]);
                    }
                }
                return this;
            },
            
            create(): void {
                const style: string = lines.join(";");
                addSelector(style);
            },
            
        }.freeze();
        
    };
    
})());