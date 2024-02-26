//
// Created on 2024/1/30.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef TURBOMODULEMANAGERDELEGATE_H
#define TURBOMODULEMANAGERDELEGATE_H

#include "react_arkui/turbo_module/ArkTSTurboModule.h"

namespace rnoh {
    class TurboModuleManagerDelegate {

    public:
        virtual std::shared_ptr<facebook::react::TurboModule> getTurboModule(ArkTSTurboModule::Context &ctx,
                                                                             const std::string &name) = 0;
    };
} // namespace rnoh
#endif // TURBOMODULEMANAGERDELEGATE_H