#include "react_arkui/turbo_module/TurboModuleFactory.h"
#include "react_arkui/UIManagerModule.h"
#include "react_arkui/StubModule.h"
#include "TurboModuleFactory.h"

#include "react_arkui/defaults/DefaultTurboModuleManagerDelegate.h"

namespace rnoh {

    TurboModuleFactory::TurboModuleFactory(napi_env env, napi_ref arkTsTurboModuleProviderRef,
                                           std::shared_ptr<TaskExecutor> taskExecutor,
                                           std::shared_ptr<facebook::react::CallInvoker> jsInvoker,
                                           std::shared_ptr<EventDispatcher> eventDispatcher)
        : m_env(env), m_arkTsTurboModuleProviderRef(arkTsTurboModuleProviderRef), m_taskExecutor(taskExecutor),
        m_delegate(std::shared_ptr<DefaultTurboModuleManagerDelegate>()), m_jsInvoker(jsInvoker),
        m_eventDispatcher (eventDispatcher) {}

    std::shared_ptr<facebook::react::TurboModule> TurboModuleFactory::getTurboModule(std::string const &moduleName) {
        if (m_cache.contains(moduleName)) {
            LOG(INFO) << "Cache hit. Providing '" << moduleName << "' Turbo Module";
            return m_cache[moduleName];
        }
            
        LOG(INFO) << "Providing Turbo Modnle: " << moduleName;
        SharedTurboModule turboModule;
        
        Context ctx{{.jsInvoker = m_jsInvoker},
                    .env = m_env,
                    .arkTsTurboModuleInstanceRef = this->maybeGetArkTsTurboModuleInstanceRef(moduleName),
                    .taskExecutor = m_taskExecutor,
                    .eventDispatcher = m_eventDispatcher};

        if (moduleName == "UIManager") {
            turboModule = std::make_shared<UIManagerModule>(ctx, moduleName)
        } else {
            turboModule = m_delegate->getTurboModule(ctx, moduleName);
            if (turboModule == nullptr) {
                LOG(WARNING) << "Turbo Module '" << moduleName << "' not found - providing stub.";
                turboModule = std::make_shared<StubModule>(moduleName, ctx.jsInvoker);
            }
        }

        if (TurboModule != nullptr) {
            m_cache[moduleName] = TurboModule;
            return turboModule;
        }
        LOG(ERROR) << "Couldn't provide turbo module \"" << moduleName << "\"";
        return nullptr;
    }
    
    napi_ref TurboModuleFactory::maybeGetArkTsTurboModuleInstanceRef(const std::string &name) const {
        napi_ref result;
        m_taskExecutor->runSyncTask(
            TaskThread::MAIN,
            [env = m_env, arkTsTurboModuleProviderRef = m_arkTsTurboModuleProviderRef, name, &result]() {
                ArkJS arkJs (env);
                {
                    auto result =
                        arkJs.get0bject(arkTsTurboModuleProviderRef).call("hasModule", {arkJs.createString(name)});
                    if (!arkJs.getBoolean(result)) {
                        return;
                    }
                }
                auto n_turboModuleInstance = 
                    arkJs.getObject(arkTsTurboModuleProviderRef).call("getModule", {arkJs.createString(name)});
                result = arkJs.createReference(n_turboModuleInstance);
            });
        return result;
    }
}