//
// Created on 2024/2/5.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "RCTView_manager.h"

namespace rnoh {

    RCTView_manager::RCTView_manager(std::string const &componentName) {
        LOG(ERROR) << "RCTView_manager::RCTView_manager. componentName is  " << componentName << "\n";
    }

    void RCTView_manager::bindingArkTsParty(aki::Value arkTS) {
        LOG(ERROR) << "RCTView_manager::bindingArkTsParty. this is  " << this << "\n";
        arkTsThis_ = arkTS;
    }

    void RCTView_manager::onDropViewInstance(int view) {
        LOG(ERROR) << "RCTView_manager::onDropViewInstance. this is  " << this << "\n";
    }
} // namespace rnoh