//
// Created on 2024/2/21.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef RCTSCROLLVIEW_MANAGER_H
#define RCTSCROLLVIEW_MANAGER_H

#include "react_arkui/fabric/view_group_manager.hpp"
#include "RCTScrollView.h"
#include <aki/jsbind.h>

using namespace facebook::react;

namespace rnoh {
    class RCTScrollView_manager : public view_group_manager<RCTScrollView> {
    public:
        RCTScrollView_manager(std::string const &componentName);
        ~RCTScrollView_manager() {}

        void bindingArkTsParty(aki::Value arkTS);

        void onDropViewInstance(int view);

        RCTScrollView *createViewInstance() {
            LOG(ERROR) << "RCTScrollView_manager::createViewInstance. this is " << this << "\n";
            return new RCTScrollView();
        }

    private:
        aki::Value arkTsThis_;
    };

    JSBIND_CLASS(RCTScrollView_manager) {
        JSBIND_CONSTRUCTOR<std::string>();
        JSBIND_METHOD(bindingArkTsParty);
    }
} // namespace rnoh
#endif // RCTSCROLLVIEW_MANAGER_H
