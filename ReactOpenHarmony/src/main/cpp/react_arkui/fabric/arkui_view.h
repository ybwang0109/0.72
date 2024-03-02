//
// Created on 2024/2/19.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef ARKUI_VIEW_H
#define ARKUI_VIEW_H

namespace rnoh {
    class arkui_view {
    public:
        virtual void createNode() = 0;
    };
} // namespace rnoh
#endif //ARKUI_VIEW_H