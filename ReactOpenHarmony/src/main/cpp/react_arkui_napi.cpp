#include "napi/native_api.h"
#include <hilog/log.h>
#include <aki/jsbind.h>
#include "react_arkui/ArkJS.h"
#include "react_arkui/fabric/RNOHFabricUIManager.h"
#include "react_arkui/LogSink.h"

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <arkui/native_interface.h>
#include <arkui/native_node.h>

#define LOG_TAG "RTNArkUI_CPP"

using namespace rnoh;

static napi_value emitEvent(napi_env env, napi_callback_info info) {
    ArkJS ark_js(env);
    auto args = ark_js.getCallbackArgs(info, 3);
    double tag, eventKind;
    napi_get_value_double(env, args[0], &tag);
    napi_get_value_double(env, args[1], &eventKind);

    //     RNOHFabricUIManager::FabricInstances->emitComponentEvent(env,
    //                                                              arkJs.getDouble(args[1]),
    //                                                              arkJs.getString(args[2]),
    //                                                              args[3]);
    return ark_js.getUndefined();
}

static void registerNativeXComponent(napi_env env, napi_value exports) {

	LOG(ERROR) << "registerNativeXComponent: begin";
 
	if ((env == nullptr) || (exports == nullptr)) {
		LOG(ERROR) << "registerNativeXComponent: env or exports is null"
				   << "\n";
		return;
	}
 
	napi_value exportInstance = nullptr;
	if (napi_get_named_property(env, exports, OH_NATIVE_XCOMPONENT_OBJ, &exportInstance) != napi_ok) {
		LOG(ERROR) << "registerNativeXComponent: napi_get_named_property fail"
				   << "\n";
		return;
	}
 
	OH_NativeXComponent *nativeXComponent = nullptr;
	if (napi_unwrap(env, exportInstance, reinterpret_cast<void **>(&nativeXComponent)) != napi_ok) {
		LOG(ERROR) << "registerNativeXComponent: napi_get_named_property fail"
				   << "\n";
		return;
	}
 
	char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
	uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
	if (OH_NativeXComponent_GetXComponentId(nativeXComponent, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
		LOG(ERROR) << "registerNativeXComponent: OH_NativeXComponent_GetXComponentId fail"
				   << "\n";
		return;
	}
 
	LOG(ERROR) << "registerNativeXComponent: idStr = " << idStr;
	RNOHFabricUIManager::XComponentSurface = nativeXComponent;
 
	LOG(ERROR) << "registerNativeXComponent: end";
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    LogSink::initializeLogging();
    napi_property_descriptor desc[] = {
        {"emitEvent", nullptr, emitEvent, nullptr, nullptr, nullptr, napi_default, nullptr}};

    napi_define_properties(env, exports, sizeof(desc) / sizeof(napi_property_descriptor), desc);

    exports = aki::JSBind::BindSymbols(env, exports);

    registerNativeXComponent(env, exports);

    return exports;
}
EXTERN_C_END

static napi_module reactArkUIModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "react_arkui",
    .nm_priv = ((void *)0),
    .reserved = {0},
};

extern "C" __attribute__((constructor)) void RegisterRnohModule(void) { napi_module_register(&reactArkUIModule); }
