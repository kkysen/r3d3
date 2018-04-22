"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.ReattachingBuffer = {
    new(supplier, detacherParent, detacherName) {
        let detacher = detacherParent[detacherName];
        if (!detacher.detacher) {
            const realDetacher = detacher;
            detacher = function (...args) {
                detacher(args);
                for (const reattacher of detacher.attached) {
                    reattacher();
                }
            };
            detacher.attached = [];
            detacher.detacher = realDetacher;
            detacherParent[detacherName] = detacher;
        }
        let value = supplier();
        detacher.attached.push(() => {
            value = supplier();
        });
        return {
            detacher: detacher,
            get() {
                return value;
            },
        };
    }
};
//# sourceMappingURL=ReattachingBuffer.js.map