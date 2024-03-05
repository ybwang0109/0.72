//
// Created on 2024/1/30.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef RNCORE_MODULEPROVIDER_H
#define RNCORE_MODULEPROVIDER_H

#include "react_arkui/turbo_module/ArkTSTurboModule.h"

namespace rnoh {

    std::shared_ptr<facebook::react::TurboModule> rncore_ModuleProvider(const std::string &moduleName,
                                                                        const ArkTSTurboModule::Context &ctx);
}
#endif // RNCORE_MODULEPROVIDER_H
