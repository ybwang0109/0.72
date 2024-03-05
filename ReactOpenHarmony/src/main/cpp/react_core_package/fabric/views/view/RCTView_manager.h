//
// Created on 2024/2/5.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

#include "react_arkui/fabric/view_group_manager.hpp"
#include "RCTView.h"
#include <aki/jsbind.h>

using namespace facebook::react;

namespace rnoh {

    class RCTView_manager : public view_group_manager<RCTView> {
    public:
        RCTView_manager(std::string const &componentName);
        ~RCTView_manager() {}

        void bindingArkTsParty(aki::Value arkTS);

        void onDropViewInstance(int view);

        RCTView *createViewInstance() {
            LOG(ERROR) << "RCTView_manager::createViewInstance. this is " << this << "\n";
            return new RCTView();
        }

    private:
        aki::Value arkTsThis_;
    };

    JSBIND_CLASS(RCTView_manager) {
        JSBIND_CONSTRUCTOR<std::string>();
        JSBIND_METHOD(bindingArkTsParty);
    }
} // namespace rnoh
#endif // VIEW_MANAGER_H
