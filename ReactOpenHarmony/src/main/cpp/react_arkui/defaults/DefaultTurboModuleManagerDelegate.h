//
// Created on 2024/1/30.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef DEFAULTTURBOMODULEMANAGERDELEGATE_H
#define DEFAULTTURBOMODULEMANAGERDELEGATE_H

#include "react_arkui/turbo_module/ArkTSTurboModule.h"
#include "react_arkui/turbo_module/TurboModuleManagerDelegate.h"

namespace rnoh {
    //todo: 需要改成继承自TurboModuleManagerDelegate，但是会闪退，没有找到原因
    class DefaultTurboModuleManagerDelegate {

    public:
        static std::function<std::shared_ptr<TurboModule>(const std::string &, const ArkTSTurboModule::Context &)>
            ArkTSModuleProvider; //用于导入开发者自定义TurboModule

        DefaultTurboModuleManagerDelegate();

        std::shared_ptr<facebook::react::TurboModule> getTurboModule(ArkTSTurboModule::Context &ctx,
                                                                     const std::string &name) ;
    };
} // namespace rnoh

#endif // DEFAULTTURBOMODULEMANAGERDELEGATE_H