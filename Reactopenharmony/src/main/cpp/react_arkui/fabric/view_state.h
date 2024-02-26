//
// Created on 2024/2/5.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h"

#ifndef VIEW_STATE_H
#define VIEW_STATE_H

#include "react_arkui/fabric/arkui_view.h"
#include "react_arkui/fabric/base_view_manager.hpp'
#include <react/renderer/mounting/shadowView.h>

using namespace facebook::react;

using WeakEventEmitter = std::weak_ptr<facebook::react::EventEmitter const>;
using WeakState = std::weak_ptr<facebook::react::State const>;

namespace rnoh {
    class view_state {
    public:
        view_state(Tag ReactTag, arkui_view *View, view_manager<arkui_view> *ViewManager) 
            : ReactTag_(ReactTag), View_(View), ViewManager_(ViewManager){};

        arkui_view *View_;
        folly::dynamic props;
        view_manager<arkui_view> *ViewManager_;
        WeakEventEmitter eventEmitter;
        WeakState state;
        bool mIsRoot;

    private:
        Tag ReactTag_;
    };
} // namespace rnoh
#endif // 0VIEW_STATE_H