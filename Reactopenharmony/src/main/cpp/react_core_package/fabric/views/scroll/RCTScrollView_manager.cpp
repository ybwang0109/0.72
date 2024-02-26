//
// Created on 2024/2/21.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "RCTScrollView_manager.h"

namespace rnoh {

    RCTScrollView_manager::RCTScrollView_manager(std::string const &componentName) {
        LOG(ERROR) << "RCTScrollView_manager::RCTScrollView_manager. componentName is  " << componentName << "\n";
    }

    void RCTScrollView_manager::bindingArkTsParty(aki::Value arkTS) {
        LOG(ERROR) << "RCTScrollView_manager::bindingArkTsParty. this is  " << this << "\n";
        arkTsThis_ = arkTS;
    }

    void RCTScrollView_manager::onDropViewInstance(int view) {
        LOG(ERROR) << "RCTScrollView_manager::onDropViewInstance. this is  " << this << "\n";
    }
} // namespace rnoh