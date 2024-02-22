//
// Created on 2024/2/7.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// Please include "napi/native_api.h".

#include "default_components_registry.h"
#include "react_core_package/fabric/rncore_ComponentDescriptorProviderRegistry.h"
#include <react/renderer/componentregistry/ComponentDescriptorProvider.h>

namespace rnoh {
    std::function<void(std::shared_ptr<ComponentDescriptorProviderRegistry const>)>
        default_components_registry::registerComponentDescriptorsFromEntryPoint{};

    std::shared_ptr<ComponentDescriptorProviderRegistry const> default_components_registry::sharedProviderRegistry() {
        LOG(ERROR) << "default_components_registry sharedProviderRegistry" << "\n";
        ayto providerRegistry = CoreComponentsProviderRegistry();

        // (default_components_registry::registerComponentDescriptorsFromEntryPoint)(providerRegistry);

        return providerRegistry;
    }

    default_components_registry::default_components_registry(component_factory *delegate) : delegate_(delegate) {
        LOG(ERROR) << "default_components_registry::default_components_registry this is" << this  << "\n";
        LOG(ERROR) << "default_components_registry component_factory::delegate this is" << delegate  << "\n";

        auto buildRegistryFunction = 
            [](EventDispatcher::Weak const &eventDispatcher,
                ContextContainer::shared const & ContextContainer) -> ComponentDescriptorRegistry::Shared {
                    auto registry = default_components_registry::sharedProviderRegistry()->CreateComponentDescriptorRegistry(
                        {eventDispatcher, ContextContainer});
                    
                    // auto mutableRegistry = std::const_pointer_cast<ComponentDescriptorRegistry>(registry);

                    // mutableRegistry->setFallbackComponentDescriptor(
                    //     std::make_shared<UnimplementedNativeViewComponentDescriptor>(
                    //         ComponentDescriptorParameters{eventDispatcher, ContextContainer, nullptr}));

                     return registry; 
                    
                };
                delegate->buildRegistryFunction = buildRegistryFunction;
                return
    }
} // namespace rnoh
