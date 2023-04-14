#pragma once
#include "napi/native_api.h"
#include <jsi/jsi.h>

#include "ArkJS.h"
#include "RNOH/TaskExecutor.h"
#include "RNOH/TurboModule.h"

namespace rnoh {

class ArkTSTurboModule : public TurboModule {
  public:
    struct Context : public TurboModule::Context {
        napi_env env;
        napi_ref arkTsTurboModuleInstanceRef;
        std::shared_ptr<TaskExecutor> taskExecutor;
    };

    ArkTSTurboModule(Context ctx, std::string name);

    facebook::jsi::Value call(facebook::jsi::Runtime &runtime,
                              const std::string &methodName,
                              const facebook::jsi::Value *args,
                              size_t argsCount);

    facebook::jsi::Value callAsync(facebook::jsi::Runtime &runtime,
                                   const std::string &methodName,
                                   const facebook::jsi::Value *args,
                                   size_t argsCount);

  private:
    Context m_ctx;
};
} // namespace rnoh
