//
// Created on 2024/2/26.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
 
 
#include "RootView_manager.h"
 
namespace rnoh {
 
    RootView_manager::RootView_manager(std::string const &componentName) {
        LOG(ERROR) << "RootView_manager::RCTView_manager. componentName is  " << componentName << "\n";
    }
 
    void RootView_manager::bindingArkTsParty(aki::Value arkTS) {
        LOG(ERROR) << "RootView_manager::bindingArkTsParty. this is  " << this << "\n";
        arkTsThis_ = arkTS;
    }
 
    void RootView_manager::onDropViewInstance(int view) {
        LOG(ERROR) << "RootView_manager::onDropViewInstance. this is  " << this << "\n";
    }
} // namespace rnoh