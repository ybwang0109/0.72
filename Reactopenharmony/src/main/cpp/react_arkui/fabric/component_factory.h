// 
// Created on 2024/2/8.
// 
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY H
#include<aki/jsbind.h>


#include <react/renderer/componentregistry/ComponentDescriptorFactory,h>

using namespace facebook::react;
namespace rnoh {
    class component factory {
    public:
        component factory();
        ComponentRegistryFactory buildRegistryFunction;
    };
    JSBIND_CLASS (component factory) { JSBIND_CONSTRUCTOP<>(); }
} // namespace rnoh
#endif //COMPONENTEACTORY_H