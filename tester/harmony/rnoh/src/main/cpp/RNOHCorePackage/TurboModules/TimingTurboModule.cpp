#include "TimingTurboModule.h"

namespace rnoh {

using namespace facebook;

static jsi::Value __hostFunction_TimingTurboModule_createTimer(
    jsi::Runtime &rt,
    react::TurboModule &turboModule,
    const jsi::Value *args,
    size_t count) {
    static_cast<ArkTSTurboModule &>(turboModule).scheduleCall(rt, "createTimer", args, count);
    return jsi::Value::undefined();
}
static jsi::Value __hostFunction_TimingTurboModule_deleteTimer(
    jsi::Runtime &rt,
    react::TurboModule &turboModule,
    const jsi::Value *args,
    size_t count) {
    static_cast<ArkTSTurboModule &>(turboModule).scheduleCall(rt, "deleteTimer", args, count);
    return jsi::Value::undefined();
}
static jsi::Value __hostFunction_TimingTurboModule_setSendIdleEvents(
    jsi::Runtime &rt,
    react::TurboModule &turboModule,
    const jsi::Value *args,
    size_t count) {
    static_cast<ArkTSTurboModule &>(turboModule).scheduleCall(rt, "setSendIdleEvents", args, count);
    return jsi::Value::undefined();
}

TimingTurboModule::TimingTurboModule(const ArkTSTurboModule::Context ctx, const std::string name) : ArkTSTurboModule(ctx, name) {
    methodMap_ = {
        {"createTimer", {4, __hostFunction_TimingTurboModule_createTimer}},
        {"deleteTimer", {1, __hostFunction_TimingTurboModule_deleteTimer}},
        {"setSendIdleEvents", {1, __hostFunction_TimingTurboModule_setSendIdleEvents}},
    };
}

} // namespace rnoh