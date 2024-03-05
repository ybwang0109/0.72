//
// Created on 2024/2/8.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef CORE_COMPONENTDESCRIPTORPROVIDERREGISTRY_H
#define CORE_COMPONENTDESCRIPTORPROVIDERREGISTRY_H
#include <react/renderer/componentregistry/ComponentDescriptorProviderRegistry.h>

namespace rnoh {

    std::shared_ptr<facebook::react::ComponentDescriptorProviderRegistry const> CoreComponentsProviderRegistry();
}
#endif //CORE_COMPONENTDESCRIPTORPROVIDERREGISTRY_H
