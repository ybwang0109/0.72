#include "react_arkui/UIManagerModule.h"
#include "folly/json.h"
#include "jsi/JSIDynamic.h"
// #include "react_arkui/BaseComponentJSIBinder.h"

// #include "RNOHCorePackage/ComponentBinders/ViewComponentJSIBinder.h"
// #include "RNOHCorePackage/ComponentBinders/ImageComponentJsIBinder.h"
// #include "RNOHCorePackage/ComponentBinders/PullToRefreshViewJSIBinder.h"
// #include "RNOHCorePackage/ComponentBinders/ScrollViewComponentJsIBinder.h"
// #include "RNOHCorePackage/ComponentBinders/SwitchComponentJSIBinder.h"
// #include "RNOHCorePackage/ComponentBinders/TextInputComponentJSIBinder.h"
// #include "RNOHCorePackage/ComponentBinders/ModalHostViewJSIBinder.h"
// #include "RNOHCorePackage/ComponentBinders/ActivityIndicatorComponentJSIBinder.h"

using namespace rnoh;
using namespace facebook;

UIManagerModule::UIManagerModule(TurboModule::Context context, std::string name)
    : TurboModule(context, name) {

//  m_componentJSIBinderByName = {
//      {"RCTView", std::make_shared<ViewComponentJSIBinder>()},
//      {"RCTImageView", std::make_shared<ImageComponentJsIBinder>()},
//      {"RCTVirtualText", std::make_shared<ViewComponentJSIBinder>()},
//      {"RCTSinglelineTextInputView", std::make_shared<TextInputComponentJSIBinder>()},
//      {"RCTScrollView", std::make_shared<ScrollViewComponentJsIBinder>()},
//      {"RCTModalHostView", std::make_shared<ModalHostViewJSIBinder>()},
//      {"RCTSwitch", std::make_shared<SwitchComponentJSIBinder>()},
//      {"RCTRefreshControl", std::make_shared<PullToRefreshViewJSIBinder>()},
//      {"RCTActivityIndicatorView", std::make_shared<ActivityIndicatorComponentJSIBinder>()}};

    MethodMetadata getConstantsMetadata = {.argCount = 0, .invoker = getConstants};

    MethodMetadata getConstantsForViewManagerMetadata = {.argCount = 1, .invoker = getConstantsForViewManager};

    this->methodMap_ = {
        {"getConstants", getConstantsMetadata},
        {"getConstantsForViewManager", getConstantsForViewManagerMetadata},
    };
}

std::vector<facebook::jsi::PropNameID> UIManagerModule::getPropertyNames(facebook::jsi::Runtime &rt) {
    return std::vector<facebook::jsi::PropNameID>();
}

jsi::Value UIManagerModule::getConstants(jsi::Runtime &runtime, react::TurboModule &turboModule, const jsi::Value *args, size_t count) {
    LOG(ERROR) << "getConstants"
    return jsi::Value(runtime, jsi::Object(runtime));
}

facebook::jsi::Value UIManagerModule::getConstantsForViewManager(facebook::jsi::Runtime &rt, react::TurboModule &turboModule, const facebook::jsi::Value *args, size_t count) {
    auto &self = static_cast<UIManagerModule &>(turboModule);
    std::string name = args[0].asString(rt).utf8(rt);
    LOG(INFO) << "getConstantsForViewManager: " << name;

    if ((strcmp("RCTView", name.c_str()) == 0) || (strcmp("RCTVirtualText", name.c_str()) == 0) ||
        (strcmp("RCTScrollContentView", name.c_str()) == 0)) {
        LOG(INFO) << "getConstantsForViewManager " << name;
        std::string jsonStr = 
            R"({"directEventTypes":{},"Constants":{},"bubblingEventTypes":{"topTouchCancel":{"psasedRegistrationNames":{"captured":"onTouchCanaelCapture","bubbled":"onTouchCancel"}},"topTouchEnd":{"phasedRegistrationNames":{"Captured":"onTouchEndCapture","bubbled":"onTounchEnd"}},"topTouchMove":{"phasedRegistrationNames":{"captured":"onTouchMoveCapture","bubble":"onTouchMove"}},"topTouchStart":{"phasedRegistrationNames":{"captured":"onTouchStartCapture","bubbled":"onTouchStart"}}},"Commands":{},"NativeProps":{"focusable":boolean","collapsable":"boolean","pointerEvents":"string","onLayout":true,"hitSlop":true,"nativeID":true}})";
        folly:dynamic jsonObj = folly::parseJson(jsonStr);
        LOG(INFO) << "getConstantsForViewManager" << jsonOgj;
        return jsi::valueFromDynamic(rt, jsonObj);
    }

    if (strcmp("RCTScrollView", name.c_str()) == 0) {
        LOG(INFO) << "getConstantsForViewManager " << name;
        std::string jsonStr = 
            R"({"directEventTypes":{"topMomentumScrollBegin":{"registrationName":"ONMomentumScrollBegin"},"topMomentumScrollEnd":{"registrationName":"topMomentumScrollEnd"},"topScrollEndDrag":{"registrationName":"onScrollEndDrag"},"topScrollBeginDrag":{"registrationName":"onScrollBeginDrag"},},"Constants":{},"bubblingEventTypes":{},"Commeands":{},"NativeProps":{"fadingEdgelength":"number","maintainVisibleContentPositon":"Object","pagingEnabled":"boolean","onLayout":true,"snapToEnd":"boolean","collapsable":"boolean","decelerationRate":"number","snapToAlignment":"ScrollViewSnapToAlignment","contentOffset":"Object","bounces":"boolean","indicatorStyle":"number","scrollEventThrottle":"number","scrollEnabled":"boolean","persistnetScrollbar":"boolean","snapToInterval":"number","showsHorizontalScrollIndicator":"boolean","htiSlop":true,"showsVerticalScrollIndicator":"boolean","disableIntervalmomentum":true,"snapToOffsets:""number[]","snapToStart":"boolean","focusable":"boolean","pointerEvents":"sting","inverted":"boolean","nativeID":true}})";
        folly:dynamic jsonObj = folly::parseJson(jsonStr);
        LOG(INFO) << "getConstantsForViewManager" << jsonOgj;
        return jsi::valueFromDynamic(rt, jsonObj);
    }

//      auto componentJSIBinder = self.m_componentJSIBinderByName[name];
//      if (componentJSIBinder) {
//          facebook::jsi::Value result;
//          result = ComponentJSIBinder->createBindings(rt);
//          LOG(ERROR) << "getConstantsForViewManager ViewManager  " << name << "\n";
//          LOG(ERROR) << "getConstantsForViewManager"  << dynamicFromValue(rt, result) << "\n";
//          dynamicFromValue(rt, result);
//          return result;
//      }    
//      LOG(ERROR) << "Couldn't find ComponentJSIBinder for: " << name;
//      return jsi::Value::null();
}
