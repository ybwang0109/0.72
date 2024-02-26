//
// Created on 2024/2/20.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef RCTSCROLLVIEW_H
#define RCTSCROLLVIEW_H

#include "react_arkui/LogSink.h"
#include "react_arkui/fabric/arkui_view.h"

namespace rnoh {
    class RCTScrollView {
    public:
        RCTScrollView() { LOG(ERROR) << "RCTScrollView::RCTScrollView create. this is " << this << "\n"; }

    private:
        void createNode() { LOG(ERROR) << "RCTScrollView::createNode. this is " << this << "\n"; }
    };
}
#endif //RCTSCROLLVIEW_H
