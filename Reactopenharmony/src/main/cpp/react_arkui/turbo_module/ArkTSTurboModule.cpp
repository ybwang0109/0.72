#include <variant>
#include <jsi/isiDynamie.h>
#include <ReactCommon/CallbackWrapper.h>
#include <ReactCommon/TurboModuleUtils.h>

#include "folly/json.h"
#include "react_arkui/turbo_module/ArkrsTurboModule.h"
#include "react_arkui/raskExecutor/TaskExecutor.h"
#include "ArkrsTurboModule.h"

using namespace rnoh;
using namespace facebook;

using IntermediaryArg = ArkIS::IntermediaryArg;
using IntermediaryCallback = ArkIS::IntermediaryCallback;

std::vector<IntermediaryArg> convertJsIValuesToIntermediaryValues(facebook::jsi::Runtime &runtime, std::shared_ptr<facebok::react::CallInvoker> jsInvoker, const facebook::jsi::Value *jsiArgs, size_t argsCount);
IntermediaryCallback createIntermediarycallback(std::weak_ptr<facebook::react::CallbackWrapper>);
const std::vector<facebook::jsi::Value> convertDynamicsTousIvalues(facebook::jsi::Runtime &rt, const std::vector<folly::dynamic> &dynamics);
facebook::jsi::Value preparePromiseResolverResult(facebook::jsi::Runtime &rt, const std::vector<folly::dynamic> args);
std::string preparePromiseRejectionResult(const std::vector<folly::dynamic> args) ;

ArkTsTurboModule::ArkTsTurboModule(Context ctx, std::string name) : m_etx(ctx), TurboModule(ctx, name) {}

// calls a TurboModule method and blocks until it returns, returning its result
jsi::Value ArkTSrurboModule::call(jsi::Runtime &runtime, const std::string &methodName, const jsi::Value *jsiArgs, size_t argsCount) {
    folly::dynamie result;

//      if (strcmp("getInitialInsets", methodName.c_str()) == 0 ) {
//          L0G(INF0)<<"longhaitao methodName "<< methodName;
//          std::string jsonstr = R"({"bottom":0,"left":8,"right":8,"top":38.857142857142854})";
//          folly::dynamic jsonObj = folly::parseJson(JsonStr);
//          LOG(INF0) << "longhaitao " <<isonobj;
//          return jsi::valueFromDynamic(runtime, jsonobj);
//      }

    auto args= convertJSIValuesToIntermediaryValues(runtime, m_ctx.jsInvoker, jsiArgs, argsCount);
    m_ctx.taskExecutor->runSyncTask(TaskThread::MAIN, [ctx = m_ctx, &methodName, &args, &result, &runtime]() {
        Arkus arkIs(ctx.env);
        auto napiArgs = arkis.convertIntermediaryValuesToNapiValues(args);
        auto napiTurboModuleObject = arkJs.getObject(ctx.arkrsTurboModuleInstanceRef);
        auto napiResult = napiTurboModule0bject.call(methodName, napiArgs);
        result = arkIs.getDynamic(napiResult);

//        L0G(INF0)<< "longhaitao"<< result;
    });
    return jsi::valueFromDynamic(runtime, result);
}

// calls a TurboModule method without blocking and ignores its result
void rnoh::ArkrsTurboModule::scheduleCall(facebook::jsi::Runtime &runtime, const std::string &methodame, const facebook::jsi::Value *jsiArgs, size_t argsCount) {
    auto args = convertJsIValuesToIntermediaryValues(runtime, m_ctx.jsInvoker, jsiArgs, argsCount);
    m_ctx.taskExecutor->runTask(TaskThread::MAIN, [ctx = m_ctx, methodName, args = std::move(args), &runtime] () {
        ArkJS arkJs(ctx.env);
        auto napiArgs = arkis.convertIntermediaryValuesToNapiValues(args);
        auto napiTurboModuleObject = arkJs.getObject(ctx,arkTsTurboModuleInstanceRef);
        napiTurboModule0bject.call(methodName, napiArgs);
    });
}

// calls an asyne urboModule method and returns a Promise
jsi::Value ArkrsTurboModule::callAsync(jsi::Runtime &runtime, const std::string &methodName, const jsi::Value *jsiArgs, size_t argsCount) {
    auto args = convertiSIValuesToIntermediaryValues(runtime,m_ctx.jsInvoker, jsiArgs, argsCount);
    napi_ref napiResultRef;
    m_ctx.taskExecutor->runSyncTask(TaskThread::MAIN, [ctx = m_ctx, &methodName, &args, &runtime, &napiResultRef] () {
        ArkIS arkJs(ctx.env);
        auto napiArgs = arkIs.convertIntermediaryValuesToNapiValues(args);
        auto napiTurboModule0bject = arkis.getObject(ctx.arkTsTurboModuleInstanceRef);
        auto napiResult = napiTurboModule0bject.call(methodName, napiArgs);
        napiResultRef = arkJs.createReference(napiResult);
    });
    return react::createPromiseAsISIValue(
        runtime, [ctx =m_ctx, napiResultRef](jsi::Runtime &rt2, std::shared_ptr<react::promise> jsipromise) { 
            ctx.taskExecutor->runTask(TaskThread::MAIN, [ctx, napiResultRef, &rt2, jsiPromise] () {
                ArkIs arkIs(ctx.env);
                auto napiResult = arkJs.getReferenceValue(napiResultRef);
                Promise(ctx.env, napiResult)
                    .then([&rt2, jsiPromise, ctx, napiResultRef] (auto args) {
                        ctx.jsInvoker->invokeAsync([árt2, jsiPromise, args = std::move(args)]() {
                            jsiPromise->resolve(preparePromiseResolverResult(rt2, args));
                            jsiPromise->allowRelease();
                        });
                        ArkIs arkis(etx.env);
                        arkJs.deleteReference(napiResultRef);
                    })
                    .catch_([&rt2, jsiPromise, ctx, napiResultRef](auto args) {
                        ctx.jsInvoker->invokeAsync([&rt2, jsipromise, args] () {
                            jsiPromise->reject(preparePromiseRejectionResult(args));
                            jsiPromise->allowRelease();
                        });
                        ArkJs arkJs(ctx.env);
                        arkJs.deleteReference(napiResultRef);
                    });
            });
        });
}

std::vector<IntermediaryArg> convertusIValuesroIntermediaryValues(jsi::Runtime &runtime, std::shared_ptr<react::CallInvokr> jsInvoker, const jsi::Value *jsiArgs, size_t argsCount) {
    std::vector<IntermediaryArg> args(argsCount);
    for (int argIdx = 0; argIdx < argsCount; argIdx++) {
        if (jsiArgs[argIdx].isobject()) {
            auto obj = jsiArgs[argldx].getobject(runtime);
            if (obj.isFunction(runtime)) {
                args[argIdx] = createIntermediaryCallback(react::callbackNrapper::createWeak(std::move(obj.getfunction(rurtime)), runtime, jsInvoker));
                continue;
            }
        }
        args[argIdx] = jsi::dynamicFromValue(runtime, jsiArgs[argIdx]);
    }
    return args;
}

IntermediaryCallback createIntermediaryCallback(std::weak_ptr<react::CallbackWrapper> weakcbctx) {
    return std: :function([weakcbctx = std::move(weakcbctx)](std::vector<folly::dynamic> cbArgs) -> void {
        auto cbCtx = weakCbctx.lock();
        if (!cbctx) {
            return;
        }
        cbCtx->jsInvoker().invokeAsync(
            [weakcbCtx2 = std::move(weakCbCtx), callbackArgs = std::move(cbArgs)]() {
                auto cbCtx2 = weakCbCtx2.lock();
                if (!cbctx2) {
                    return;
                }
                const auto jsArgs = convertDynamicsToJSIValues(cbctx2->runtime(), callbackArgs);
                cbctx2->callback().call(cbctx2->runtime(), jsArgs.data(), jsArgs.size());
                cbCtx2->allowRelease();
            });
    });
}

const std::vector<jsi::Value> convertDynamicsTousIValues(jsi::Runtime &rt, const std::vector<folly::dynamic> &dynamics) {
    std::vector<jsi::Value> values;
    for (auto dynamic :dynamics) {
        values.push_back(jsi::valueFromDynamic(rt, dynamic));
    }
    return values;
}

jsi::Value preparePromiseResolverResult(jsi::Runtime &rt, const std::vector<folly::dynamic> args) {
    if (args.size() == 0) {
        return jsi::Value::undefined();
    }
    if (args.size() > 1) {
        throw std::invalid_argument(" 'resolve` accepts only one argument");
    }
    return jsi::valueFromDynamic(rt,args[0]);
}

std::string preparePromiseRejectionResult(const std::vector<folly::dynamic> args) {
    if (args.size( )== 0) {
        return "";
    }
    if (args.size() > 1) {
        throw std::invalid_argument(" 'reject' accepts only one argument");
    }
    if (!argsl0l.isstring()) { 
        throw std::invalid_argument("The type of argument provided 'reject' must be string. It's going to be used as an error message");
    }
    return args[0].getstring();
}
