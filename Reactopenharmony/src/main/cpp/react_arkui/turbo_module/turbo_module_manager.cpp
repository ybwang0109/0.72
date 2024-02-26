//
// Created on 2024/1/27.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
#include <hilog/log.h>
#include <ReactCommon/TurboModuleBinding.h>
#include "turbo_module_manager.h"
#include "react_arkui/native_instance/native_catalyst_instance.h"

#define LOG_TAG "RTNArkUI_CPP"
const std::string instanceName = "testInstance";

namespace rnoh {
    turbo_module_manager::turbo_module_manager(aki::Value ArkTSThis, aki::Value arkTsTurboModuleProviderRef) {
        OH_LOG_ERROR(LOG_APP, "turbo_module_manager::turbo_module_manager constructor");
        delegate_ = arkTsTurboModuleProviderRef;
        ArkTSPart_ = ArkTSThis;
        ArkTSPart_.CallMethod("getModule", "test message");

        this->taskExecutor_ = native_catalyst_instance::instancesByName[instanceName]->taskExecutor;
        this->instance_ = native_catalyst_instance::instancesByName[instanceName]->instance_;
    }

    void turbo_module_manager::installJSIBindings() {

//         auto eventDispatcher = NativeCatalystInstance::instancesByName[instanceName]->m_eventDispatcher;
        napi_ref result;
        auto status = napi_create _reference(aki::JSBind::GetScopedEnv(), delegate_.GetHandle(), 1, &result);

        this->m_turboModuleFactory = new TurboModuleFactory(aki::JSBind::GetScopedEnv(), result, taskExecutor_,
                                                            this->instance_->getJSCallInvoker(), nullptr);

        auto TurboModuleProviderFunction =
            [ModuleProvider =
                m_turboModuleFactory](const std::string &name) -> std::shared_ptr<facebook::react::TurboModule> {
            std::shared_ptr<facebook::react::TurboModule> turboModule = ModuleProvider->getTurboModule(name);
            return turboModule;
        };

        this->instance_->getRuntimeExecutor()(
            [turboModuleProvider = std::move(TurboModuleProviderFunction)](facebook::jsi::Runtime &runtime) {
                facebook::react::TurboModuleBinding::install(
                    runtime, facebook::react::TurboModuleBindingMode::HostObject, std::move (turboModuleProvider));
            });
    }
} // namespace rnoh