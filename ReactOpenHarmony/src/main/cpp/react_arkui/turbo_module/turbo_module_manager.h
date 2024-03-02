//
// Created on 2024/1/27.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef NEW_DEV_TURBO_MODULE_MANAGER_H
#define NEW_DEV_TURBO_MODULE_MANAGER_H

#include <cxxreact/Instance.h>
#include <ReactCommon/TurboModule.h>

#include "react_arkui/TaskExecutor/TaskExecutor.h"
#include "react_arkui/turbo_module/TurboModuleFactory.h"

#include <aki/jsbind.h>

namespace rnoh {
    class turbo_module_manager {

        using TurboModuleCache = std::unordered_map<std::string, std::shared_ptr<facebook::react::TurboModule>>;

    public:
        turbo_module_manager(aki::Value ArkTSThis, aki::Value arkTsTurboModuleProviderRef);
        void installJSIBindings();

    private:
        std::shared_ptr<TaskExecutor> taskExecutor_;
        std::shared_ptr<facebook::react::Instance> instance_;

        aki::Value ArkTSPart_;
        aki::Value delegate_;
        std::shared_ptr<TurboModuleCache> turboModuleCache_;
        rnoh::TurboModuleFactory *m_turboModuleFactory;
    };

    JSBIND_CLASS(turbo_module_manager) {
        JSBIND_CONSTRUCTOR<aki::Value, aki::Value>();
        JSBIND_METHOD(installJSIBindings);
    }
} // namespace rnoh

#endif // NEW_DEV_TURBO_MODULE_MANAGER_H
