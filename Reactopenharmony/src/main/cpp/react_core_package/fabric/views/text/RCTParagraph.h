//
// Created on 2024/2/20.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef RCTVIRTUALTEXT_H
#define RCTVIRTUALTEXT_H

#include "react_arkui/LogSink.h"
#include "react_arkui/fabric/arkui_view.h"

namespace rnoh {
    class RCTParagraph : public arkui_view {
    public:
        RCTParagraph() { LOG(ERROR) << "RCTParagraph::RCTParagraph create. this is " << this << "\n"; }

    private:
        void createNode() { LOG(ERROR) << "RCTParagraph::createNode. this is " << this << "\n"; }
    };
}
#endif //RCTVIRTUALTEXT_H
