//
// Created on 2024/1/30.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "rncore_ModuleProvider.h"
#include "DeviceInfoTurboModule.h"
#include "SafeAreaTurboModule.h"

namespace rnoh {

    std::shared_ptr<facebook::react::TurboModule> rncore_ModuleProvider(const std::string &moduleName,
                                                                        const ArkTSTurboModule::Context &ctx) {
        if (moduleName == "DeviceInfo") {
            return std::make_shared<DeviceInfoTurboModule>(ctx, moduleName);
        } else if (moduleName == "SafeAreaTurboModule") {
            return std::make_shared<SafeAreaTurboModule>(ctx, moduleName);
        }
        return nullptr;
    }

} // namespace rnoh