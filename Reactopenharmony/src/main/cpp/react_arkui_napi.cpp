#include "napi/native_api.h"
#include <hilog/log.h>
#include <aki/jsbind.h>
#include "react_arkui/ArkJS.h"
#include "react_arkui/fabric/RNOHFabricUIManager.h"
#include "react_arkui/LogSink.h"

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

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
	LogSink::initializeLogging();
	napi_property_descriptor desc[] = {
		{"emitEvent", nullptr, emitEvent, nullptr, nullptr, nullptr, napi_default, nullptr}
	};

	napi_define_properties(env, exports, sizeof(desc) / sizeof(napi_property_descriptor), desc);

	exports = aki::JSBind::BindSymbols(env, exports);

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
	