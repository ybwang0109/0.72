//
// Created on 2024/2/7.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef DEFAULTCOMPONENTSREGISTRY_H
#define DEFAULTCOMPONENTSREGISTRY_H
#include <aki/jsbind.h>

#include <react/renderer/componentregistry/ComponentDescriptorProviderRegistry.h>
#include <react_arkui/fabric/component_factory.h>

using namespace facebook::react;

namespace rnoh {
    class default_components_registry {
    public:
        static std::function<void(std::shared_ptr<ComponentDescriptorProviderRegistry const>)>
            registerComponentDescriptorsFromEntryPoint; //用于导入开发者自定义Component
        default_components_registry(component_factory *delegate);

    private:
        static std::shared_ptr<ComponentDescriptorProviderRegistry const> sharedProviderRegistry();
        const component_factory *delegate_;
    };

    JSBIND_CLASS(default_components_registry) { JSBIND_CONSTRUCTOR<component_factory *>(); }
} // namespace rnoh
#endif // DEFAULTCOMPONENTSREGISTRY_H