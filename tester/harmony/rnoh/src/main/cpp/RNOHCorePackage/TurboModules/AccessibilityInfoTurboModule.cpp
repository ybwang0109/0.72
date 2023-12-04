/**
 * This code was generated by [react-native-codegen](https://www.npmjs.com/package/react-native-codegen).
 *
 * Do not edit this file as changes may cause incorrect behavior and will be lost
 * once the code is regenerated.
 *
 * @generated by codegen project: GenerateModuleJniCpp.js
 */

#include "AccessibilityInfoTurboModule.h"

using namespace rnoh;
using namespace facebook;

static jsi::Value __hostFunction_AccessibilityInfoTurboModule_getCurrentBoldTextState(facebook::jsi::Runtime& rt, react::TurboModule &turboModule, const jsi::Value* args, size_t count) {
  return static_cast<ArkTSTurboModule &>(turboModule).call(rt, "getCurrentBoldTextState", args, count);
}

static jsi::Value __hostFunction_AccessibilityInfoTurboModule_getCurrentGrayscaleState(facebook::jsi::Runtime& rt, react::TurboModule &turboModule, const jsi::Value* args, size_t count) {
  return static_cast<ArkTSTurboModule &>(turboModule).call(rt, "getCurrentGrayscaleState", args, count);
}

static jsi::Value __hostFunction_AccessibilityInfoTurboModule_getCurrentInvertColorsState(facebook::jsi::Runtime& rt, react::TurboModule &turboModule, const jsi::Value* args, size_t count) {
  return static_cast<ArkTSTurboModule &>(turboModule).call(rt, "getCurrentInvertColorsState", args, count);
}

static jsi::Value __hostFunction_AccessibilityInfoTurboModule_getCurrentReduceMotionState(facebook::jsi::Runtime& rt, react::TurboModule &turboModule, const jsi::Value* args, size_t count) {
  return static_cast<ArkTSTurboModule &>(turboModule).call(rt, "getCurrentReduceMotionState", args, count);
}

static jsi::Value __hostFunction_AccessibilityInfoTurboModule_getCurrentPrefersCrossFadeTransitionsState(facebook::jsi::Runtime& rt, react::TurboModule &turboModule, const jsi::Value* args, size_t count) {
  return static_cast<ArkTSTurboModule &>(turboModule).call(rt, "getCurrentPrefersCrossFadeTransitionsState", args, count);
}

static jsi::Value __hostFunction_AccessibilityInfoTurboModule_getCurrentReduceTransparencyState(facebook::jsi::Runtime& rt, react::TurboModule &turboModule, const jsi::Value* args, size_t count) {
  return static_cast<ArkTSTurboModule &>(turboModule).call(rt, "getCurrentReduceTransparencyState", args, count);
}

static jsi::Value __hostFunction_AccessibilityInfoTurboModule_getCurrentVoiceOverState(facebook::jsi::Runtime& rt, react::TurboModule &turboModule, const jsi::Value* args, size_t count) {
  return static_cast<ArkTSTurboModule &>(turboModule).call(rt, "getCurrentVoiceOverState", args, count);
}

static jsi::Value __hostFunction_AccessibilityInfoTurboModule_setAccessibilityContentSizeMultipliers(facebook::jsi::Runtime& rt, react::TurboModule &turboModule, const jsi::Value* args, size_t count) {
  return static_cast<ArkTSTurboModule &>(turboModule).call(rt, "setAccessibilityContentSizeMultipliers", args, count);
}

static jsi::Value __hostFunction_AccessibilityInfoTurboModule_setAccessibilityFocus(facebook::jsi::Runtime& rt, react::TurboModule &turboModule, const jsi::Value* args, size_t count) {
  return static_cast<ArkTSTurboModule &>(turboModule).call(rt, "setAccessibilityFocus", args, count);
}

static jsi::Value __hostFunction_AccessibilityInfoTurboModule_announceForAccessibility(facebook::jsi::Runtime& rt, react::TurboModule &turboModule, const jsi::Value* args, size_t count) {
  return static_cast<ArkTSTurboModule &>(turboModule).call(rt, "announceForAccessibility", args, count);
}

static jsi::Value __hostFunction_AccessibilityInfoTurboModule_announceForAccessibilityWithOptions(facebook::jsi::Runtime& rt, react::TurboModule &turboModule, const jsi::Value* args, size_t count) {
  return static_cast<ArkTSTurboModule &>(turboModule).call(rt, "announceForAccessibilityWithOptions", args, count);
}

AccessibilityInfoTurboModule::AccessibilityInfoTurboModule(const ArkTSTurboModule::Context ctx, const std::string name)
  : ArkTSTurboModule(ctx, name) {
  methodMap_["getCurrentBoldTextState"] = MethodMetadata {2, __hostFunction_AccessibilityInfoTurboModule_getCurrentBoldTextState};
  methodMap_["getCurrentGrayscaleState"] = MethodMetadata {2, __hostFunction_AccessibilityInfoTurboModule_getCurrentGrayscaleState};
  methodMap_["getCurrentInvertColorsState"] = MethodMetadata {2, __hostFunction_AccessibilityInfoTurboModule_getCurrentInvertColorsState};
  methodMap_["getCurrentReduceMotionState"] = MethodMetadata {2, __hostFunction_AccessibilityInfoTurboModule_getCurrentReduceMotionState};
  methodMap_["getCurrentPrefersCrossFadeTransitionsState"] = MethodMetadata {2, __hostFunction_AccessibilityInfoTurboModule_getCurrentPrefersCrossFadeTransitionsState};
  methodMap_["getCurrentReduceTransparencyState"] = MethodMetadata {2, __hostFunction_AccessibilityInfoTurboModule_getCurrentReduceTransparencyState};
  methodMap_["getCurrentVoiceOverState"] = MethodMetadata {2, __hostFunction_AccessibilityInfoTurboModule_getCurrentVoiceOverState};
  methodMap_["setAccessibilityContentSizeMultipliers"] = MethodMetadata {1, __hostFunction_AccessibilityInfoTurboModule_setAccessibilityContentSizeMultipliers};
  methodMap_["setAccessibilityFocus"] = MethodMetadata {1, __hostFunction_AccessibilityInfoTurboModule_setAccessibilityFocus};
  methodMap_["announceForAccessibility"] = MethodMetadata {1, __hostFunction_AccessibilityInfoTurboModule_announceForAccessibility};
  methodMap_["announceForAccessibilityWithOptions"] = MethodMetadata {2, __hostFunction_AccessibilityInfoTurboModule_announceForAccessibilityWithOptions};
}