#include "hermes/executor/HermesExecutorFactory.h"

#include "native_catalyst_instance.h"
#include "react_arkui/NativeLogger.h"
#include "react_arkui/MessageQueueThread.h"
#include "react_arkui/jsbundle.h"
#include "react_arkui/jsbundleBenchMark.h"

using namespace facebook;
namespace rnoh {

    std::unordered_map<std::string, std::unique_ptr<native_catalyst_instance>> native_catalyst_instance::instancesByName;

    void addInstanceToStaticMap(native_catalyst_instance *inputInstance, std::string inputInstanceName) {
        std::unique_ptr<native_catalyst_instance> CatalystInstance;
        CatalystInstance.reset(inputInstance);
        native_catalyst_instance::instancesByName[inputInstanceName] = std::move(CatalystInstance);
    }

    native_catalyst_instance::native_catalyst_instance(std::string instanceName)
        : instance_(std::make_shared<facebook::react::Instance>()),
          taskExecutor(std::make_shared<TaskExecutor>(
              aki::JSBind::GetScopedEnv())) { // todo:将来TaskExecutor可以被单独创建，作为参数传递进来。
        LOG(INFO) << "NativeCatalystInstance::NativeCatalystInstance. instanceName is " << instanceName << "\n";
        addInstanceToStaticMap(this, instanceName);
    }

    native_catalyst_instance::~native_catalyst_instance() {}

    void native_catalyst_instance::initializeBridge() {
        LOG(INFO) << "NativeCatalystInstance::initializeBridge."
                  << "\n";

        std::vector<std::unique_ptr<react::NativeModule>> modules;
        auto instanceCallback =
            std::make_unique<react::InstanceCallback>(); // todo: 实现CallBack相关能力，保证同一时刻，只能有一个JSCall
        auto jsExecutorFactory = std::make_shared<react::HermesExecutorFactory>(
            // runtime installer, which is run when the runtime
            // is first initialized and provides access to the runtime
            // before the JS code is executed
            [](facebook::jsi::Runtime &rt) {
                // install `console.log` (etc.) implementation
                react::bindNativeLogger(rt, nativeLogger);
            });

        // todo: MessageQueueThread封装同步runable和异步runable，TaskRunner封装屏蔽ArkJS线程和非ArkJS线程的差异。
        auto React_jsQueue = std::make_shared<MessageQueueThread>(this->taskExecutor);
        auto moduleRegistry = std::make_shared<react::ModuleRegistry>(std::move(modules));
        this->instance_->initializeBridge(std::move(instanceCallback), std::move(jsExecutorFactory),
                                          std::move(React_jsQueue), std::move(moduleRegistry));
    }

    void native_catalyst_instance::loadScriptFromFile(const std::string &fileName, const std::string &sourceURL,
                                                    bool loadSynchronously) {
        LOG(INFO) << "NativeCatalystInstance::loadScriptFromFile().";
        // todo:实现真实的文件加载能力
        //      auto unique_js_bundle = std::make_unique<facebook::react::JSBigStdString>(JS_BUNDLE);  //
        //      适配工程最早的Bundle文件，appkey=rnempty
        auto unique_js_bundle = std::make_unique<facebook::react::JSBigStdString>(
            JS_BenchMark_BUNDLE); // BenchMark的Bundle文件，appkey=app_name
        this->instance_->loadScriptFromString(std::move(unique_js_bundle), "jsBundle.js", true);
    }

    void rnoh::native_catalyst_instance::onMemoryLevel(size_t memoryLevel) {
        LOG(INFO) << "NativeCatalystInstance::onMemoryLevel().";
            // Android memory levels are 5, 10, 15, while Ark's are 0, 1, 2
        static const int memoryLevels[] = {5, 10, 15};
        if (this->instance_) {
            this->instance_->handleMemoryPressure(memoryLevels[memoryLevel]);
        }
    }

    void native_catalyst_instance::callJSFunction(std::string &&module, std::string &&method, folly::dynamic &&params) {
        LOG(INFO) << "NativeCatalystInstance::callJSFunction(). module " << module << " method " << method << " params "
                  << params;
        instance_->callJSFunction(std::move(module), std::move(method), std::move(params));
    }

    facebook::react::RuntimeExecutor native_catalyst_instance::getRuntimeExecutor() {
        LOG(INFO) << "NativeCatalystInstance::getRuntimeExecutor().";
        if (!runtimeExecutor_) {
            runtimeExecutor_ = instance_->getRuntimeExecutor();
        }
        return runtimeExecutor_;
    }

} // namespace rnoh