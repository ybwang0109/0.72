// NOTE: This entire file should be codegen'ed.

#include "BlobTurboModule.h"

using namespace rnoh;
using namespace facebook;

static jsi::Value __hostFunction_BlobTurboModule_addNetworkingHandler(
    jsi::Runtime &rt,
    react::TurboModule &turboModule,
    const jsi::Value *args,
    size_t count) {
    return static_cast<ArkTSTurboModule &>(turboModule).call(rt, "addNetworkingHandler", args, count);
}

BlobTurboModule::BlobTurboModule(const ArkTSTurboModule::Context ctx, const std::string name)
    : ArkTSTurboModule(ctx, name) {
    methodMap_["addNetworkingHandler"] = MethodMetadata{0, __hostFunction_BlobTurboModule_addNetworkingHandler};
}