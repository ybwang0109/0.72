#ifndef native_CatalystInstance_H
#define native_CatalystInstance_H

#include <cxxreact/Instance.h>
#include <react/renderer/componentregistry/ComponentDescriptorProviderRegistry.h>
#include "ReactCommon/RuntimeExecutor.h"
#include "react_arkui/TaskExecutor/TaskExecutor.h"
#include "react_arkui/fabric/SchedulerDelegate.h"

#include <aki/jsbind.h>

namespace rnoh {

    class native_catalyst_instance {
    public:
        native_catalyst_instance(std::string instanceName);
        ~native_catalyst_instance();

        void initializeBridge();
        void loadScriptFromFile(const std::string &fileName, const std::string &sourceURL, bool loadSynchronously);
        void callJSFunction(std::string &&module, std::string &&method, folly::dynamic &&params);
        void onMemoryLevel(size_t memoryLevel);

        facebook::react::RuntimeExecutor getRuntimeExecutor();

        std::shared_ptr<TaskExecutor> taskExecutor;
        std::shared_ptr<facebook::react::Instance> instance_; // todo: 需要改成私有成员，不直接对外可见。
        
        // todo: 需要与Fabric共享的内容
        std::shared_ptr<facebook::react::ComponentDescriptorProviderRegistry> m_componentDescriptorProviderRegistry;

        static std::unordered_map<std::string, std::unique_ptr<native_catalyst_instance>>instancesByName;

    private:
        std::string instanceName;
        facebook::react::RuntimeExecutor runtimeExecutor_;
    };

    JSBIND_CLASS(native_catalyst_instance) {
        JSBIND_CONSTRUCTOR<std::string>();
        JSBIND_METHOD(initializeBridge);
        JSBIND_METHOD(loadScriptFromFile);
    }

} // namespace rnoh
#endif // native_CatalystInstance_H

