//
// Created on 2024/1/30.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "DefaultTurboModuleManagerDelegate.h"
#include "react_core_package/turbo_module/rncore_ModuleProvider.h"

namespace rnoh {
    std::function<std::shared_ptr<TurboModule>(const std::string &, const ArkTSTurboModule::Context &)>
        DefaultTurboModuleManagerDelegate::ArkTSModuleProvider{nullptr};

    DefaultTurboModuleManagerDelegate::DefaultTurboModuleManagerDelegate(){};

    std::shared_ptr<facebook::react::TurboModule>
    DefaultTurboModuleManagerDelegate::getTurboModule(ArkTSTurboModule::Context &ctx, const std::string &name) {

        auto moduleProvider = DefaultTurboModuleManagerDelegate::ArkTSModuleProvider;
        if (moduleProvider) {
            if (auto resolvedModule = moduleProvider(name, ctx)) {
                return resolvedModule;
            }
        }
        return rncore_ModuleProvider(name, ctx);
    }
} // namespace rnoh
