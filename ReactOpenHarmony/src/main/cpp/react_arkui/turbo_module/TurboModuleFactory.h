#pragma once

#include "napi/native_api.h"
#include <ReactCommon/TurboModule.h>
#include "react_arkui/turbo_module/ArkTSTurboModule.h"
#include "react_arkui/defaults/DefaultTurboModuleManagerDelegate.h"

namespace rnoh {

    class TurboModuleFactory {
    public:
        using Context = ArkTSTurboModule::Context;
        using SharedTurboModule = std::shared_ptr<facebook::react::TurboModule>;

        TurboModuleFactory(napi_env env, napi_ref arkTsTurboModuleProviderRef, std::shared_ptr<TaskExecutor>,
                           std::shared_ptr<facebook::react::CallInvoker> jsInvoker,
                           std::shared_ptr<EventDispatcher> eventDispatcher);

        std::shared_ptr<facebook::react::TurboModule> getTurboModule(std::string const &moduleName);

    protected:

        napi_ref maybeGetArkTsTurboModuleInstanceRef(const std::string &name) const;

        napi_env m_env;
        napi_ref m_arkTsTurboModuleProviderRef;
        std::shared_ptr<TaskExecutor> m_taskExecutor;
        std::shared_ptr<DefaultTurboModuleManagerDelegate> m_delegate;

    private:
        std::shared_ptr<facebook::react::CallInvoker> m_jsInvoker;
        facebook::butter::map<std::string, std::shared_ptr<facebook::react::TurboModule>> m_cache;
        std::shared_ptr<EventDispatcher> m_eventDispatcher;
    };

} // namespace rnoh