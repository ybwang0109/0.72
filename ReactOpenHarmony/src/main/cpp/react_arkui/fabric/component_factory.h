//
// Created on 2024/2/7.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H
#include <aki/jsbind.h>

#include <react/renderer/componentregistry/ComponentDescriptorFactory.h>

using namespace facebook::react;
namespace rnoh {
    class component_factory {
    public:
        component_factory();
        ComponentRegistryFactory buildRegistryFunction;
    };
    JSBIND_CLASS(component_factory) { JSBIND_CONSTRUCTOR<>(); }
} // namespace rnoh

#endif //COMPONENTFACTORY_H