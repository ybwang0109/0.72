//
// Created on 2024/2/19.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef RCTVIEW_H
#define RCTVIEW_H

#include "react_arkui/LogSink.h"
#include "react_arkui/fabric/arkui_view.h"

namespace rnoh {
    class RCTView : public arkui_view {
    public:
        RCTView() { LOG(ERROR) << "RCTView::RCTView create. this is " << this << "\n"; }

    private:
        void createNode() { LOG(ERROR) << "RCTView::createNode. this is " << this << "\n"; }
    };
} // namespace rnoh
#endif //0_72_NEW_DEV_RCTVIEW_H
