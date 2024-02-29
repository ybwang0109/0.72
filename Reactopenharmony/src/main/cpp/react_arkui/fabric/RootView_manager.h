//
// Created on 2024/2/25.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
 
#ifndef ROOTVIEW_MANAGER_H
#define ROOTVIEW_MANAGER_H
 
#include "react_arkui/fabric/RootView.h"
#include "react_arkui/fabric/view_group_manager.hpp"
#include <aki/jsbind.h>
 
namespace rnoh {
 
    class RootView_manager : public view_group_manager<RootView> {
    public:
        RootView_manager(std::string const &componentName);
        ~RootView_manager() {}
 
        void bindingArkTsParty(aki::Value arkTS);
 
        void onDropViewInstance(int view);
 
        RootView *createViewInstance() {
            LOG(ERROR) << "RootView_manager::createViewInstance. this is " << this << "\n";
            return new RootView();
        }
 
    private:
        aki::Value arkTsThis_;
    };
 
    JSBIND_CLASS(RootView_manager) {
        JSBIND_CONSTRUCTOR<std::string>();
        JSBIND_METHOD(bindingArkTsParty);
    }
 
} // namespace rnoh
 
#endif //ROOTVIEW_MANAGER_H