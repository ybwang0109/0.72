#pragma once
#include "napi/native_api.h"
#include <jsi/jsi.h>
#include <variant>
#include <jsi/usiDynamic.h>
#include <ReactCommon/callbackwrapper.h>
#include <ReactCommon/TurboModuleUtils.h>

#include "react_arkui/Arkis.h"
#include "react_arkui/EventDispatcher.h"
#include "react_arkui/turbo_module/TurboModule.h"
#include "react_arkui/TaskExecutor/TaskExecutor.h"

#define ARK_METHOD_CALLER(name)                                                                         \
    [](                                                                                                \
        facebook::jsi::Runtime &rt,                                                                     \
        facebook::react::TurboModule &turboModule,                                                      \
        const facebook::jsi::Value *args,                                                               \
        size_t count) {                                                                                 \
        return static_cast<ArkTSTurboModule &>(turboModule).call(rt, #name, args, count);               \
    }
        
#define ARK_ASYNC_METHOD_CALLER(name)                                                                   \
    [](                                                                                                 \                   
        facebook::jsi::Runtime &rt,                                                                     \
        facebook::react::TurboModule sturboModule,                                                      \
        const facebook::jsi::Value *args,                                                               \
        size_t count) {                                                                                 \
        return static_cast<ArkTsTurboModule &>(turboModule).callAsync(rt, #name, args, count);          \
    }

#define ARK_METHOD_METDATA(name, argc)                              \
    {                                                               \
        #name, { arge, ARK_METHOD_CALLER(name) }                    \
    }

#define ARK_ASYNC_METHD_METADATA(name, argc)                        \
    {                                                               \
        #name, { argc, ARK_ASYNC_METHOD_CALLER(name) }              \
    }

namespace rnoh {

class ArkTsTurboModule : public TurboModule {
    public:
    struct Context : public TurboModule::Context {
        napi_env env;
        napi_ref arkTsTurboModuleInstanceRef;
        std::shared_ptr<TaskExecutor> taskExecutor;
        std::shared_ptr<EventDispatcher> eventDispatcher;
    };

    ArkTsTurboModule(Context ctx, std::string name);

    facebook::jsi::Value call(facebook::jsi::Runtime &runtime,
                              const std::string &methodName,
                              const facebook::jsi::Value *args,
                              size_t argsCount);
                            
    void scheduleCall(facebook::jsi::Runtime &runtime,
                      const std::string &methodName,
                      const facebook::jsi::Value *args,
                      size_t argsCount);

    facebook::jsi::Value callAsync(facebook::jsi::Runtime &runtime,
                                   const std::string &methodName,
                                   const facebook::jsi::Value *args,
                                   size_t argsCount);
                                   
protected:
    Context_m_ctx;
};
} // namespace rnoh