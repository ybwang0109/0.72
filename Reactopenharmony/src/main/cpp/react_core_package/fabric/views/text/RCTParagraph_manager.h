//
// Created on 2024/2/20.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef RCTPARAGRAPH_MANAGER_H
#define RCTPARAGRAPH_MANAGER_H

#include "react_arkui/fabric/base_view_manager.hpp"
#include "RCTParagraph.h"
#include <aki/jsbind.h>

using namespace facebook::react;

namespace rnoh {
    class RCTParagraph_manager : public base_view_manager<RCTParagraph> {
    public:
        RCTParagraph_manager(std::string const &componentName);
        ~RCTParagraph_manager() {}

        void bindingArkTsParty(aki::Value arkTS);

        void onDropViewInstance(int view);

        RCTParagraph *createViewInstance() {
            LOG(ERROR) << "RCTParagraph_manager::createViewInstance. this is " << this << "\n";
            return new RCTParagraph();
        }

    private:
        aki::Value arkTsThis_;
    };

    JSBIND_CLASS(RCTParagraph_manager) {
        JSBIND_CONSTRUCTOR<std::string>();
        JSBIND_METHOD(bindingArkTsParty);
    }
} // namespace rnoh
#endif // RCTPARAGRAPH_MANAGER_H
