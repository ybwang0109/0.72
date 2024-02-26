//
// Created on 2024/2/20.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "RCTParagraph_manager.h"

namespace rnoh {

    RCTParagraph_manager::RCTParagraph_manager(std::string const &componentName) {
        LOG(ERROR) << "RCTParagraph_manager::RCTParagraph_manager. componentName is  " << componentName << "\n";
    }

    void RCTParagraph_manager::bindingArkTsParty(aki::Value arkTS) {
        LOG(ERROR) << "RCTParagraph_manager::bindingArkTsParty. this is  " << this << "\n";
        arkTsThis_ = arkTS;
    }

    void RCTParagraph_manager::onDropViewInstance(int view) {
        LOG(ERROR) << "RCTParagraph_manager::onDropViewInstance. this is  " << this << "\n";
    }
} // namespace rnoh