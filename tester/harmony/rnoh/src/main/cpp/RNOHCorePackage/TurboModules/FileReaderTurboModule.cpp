/**
 * This code was generated by [react-native-codegen](https://www.npmjs.com/package/react-native-codegen).
 *
 * Do not edit this file as changes may cause incorrect behavior and will be lost
 * once the code is regenerated.
 *
 * @generated by codegen project: GenerateModuleJniCpp.js
 */

#include "FileReaderTurboModule.h"

using namespace rnoh;
using namespace facebook;

static jsi::Value __hostFunction_FileReaderTurboModule_readAsDataURL(jsi::Runtime& rt, react::TurboModule &turboModule, const jsi::Value* args, size_t count) {
  return static_cast<ArkTSTurboModule &>(turboModule).call(rt, "readAsDataURL", args, count);
}

static jsi::Value __hostFunction_FileReaderTurboModule_readAsText(jsi::Runtime& rt, react::TurboModule &turboModule, const jsi::Value* args, size_t count) {
  return static_cast<ArkTSTurboModule &>(turboModule).call(rt, "readAsText", args, count);
}

FileReaderTurboModule::FileReaderTurboModule(const ArkTSTurboModule::Context ctx, const std::string name)
  : ArkTSTurboModule(ctx, name) {
  methodMap_["readAsDataURL"] = MethodMetadata {1, __hostFunction_FileReaderTurboModule_readAsDataURL};
  methodMap_["readAsText"] = MethodMetadata {2, __hostFunction_FileReaderTurboModule_readAsText};
}