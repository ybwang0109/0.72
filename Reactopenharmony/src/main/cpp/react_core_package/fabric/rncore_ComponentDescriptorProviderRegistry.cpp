//
// Created on 2024/2/8.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "rncore_ComponentDescriptorProviderRegistry.h"

#include <react/renderer/componentregistry/ComponentDescriptorProvider.h>
#include <react/renderer/components/view/ViewComponentDescriptor.h>
#include <react/renderer/components/image/ImageComponentDescriptor.h>
#include <react/renderer/components/text/TextComponentDescriptor.h>
#include <react/renderer/components/text/RawTextComponentDescriptor.h>
#include <react/renderer/components/text/ParagraphComponentDescriptor.h>
#include <react/renderer/components/textinput/TextInputComponentDescriptor.h>
#include <react/renderer/components/scrollview/ScrollViewComponentDescriptor.h>
#include <react/renderer/components/rncore/ComponentDescriptors.h>
#include <react/renderer/components/modal/ModalHostViewComponentDescriptor.h>

namespace rnoh {

    std::vector<facebook::react::ComponentDescriptorProvider> createComponentDescriptorProviders() {
        return {
            facebook::react::concreteComponentDescriptorProvider<facebook::react::ViewComponentDescriptor>(),
            facebook::react::concreteComponentDescriptorProvider<facebook::react::ImageComponentDescriptor>(),
            facebook::react::concreteComponentDescriptorProvider<facebook::react::TextComponentDescriptor>(),
            facebook::react::concreteComponentDescriptorProvider<facebook::react::RawTextComponentDescriptor>(),
            facebook::react::concreteComponentDescriptorProvider<facebook::react::ParagraphComponentDescriptor>(),
            facebook::react::concreteComponentDescriptorProvider<facebook::react::TextInputComponentDescriptor>(),
            facebook::react::concreteComponentDescriptorProvider<facebook::react::ScrollViewComponentDescriptor>(),
            facebook::react::concreteComponentDescriptorProvider<
                facebook::react::PullToRefreshViewComponentDescriptor>(),
            facebook::react::concreteComponentDescriptorProvider<facebook::react::ModalHostViewComponentDescriptor>(),
            facebook::react::concreteComponentDescriptorProvider<facebook::react::SwitchComponentDescriptor>(),
            facebook::react::concreteComponentDescriptorProvider<
                facebook::react::ActivityIndicatorViewComponentDescriptor>()};
    }


    std::shared_ptr<facebook::react::ComponentDescriptorProviderRegistry const> CoreComponentsProviderRegistry() {

        auto componentDescriptorProviderRegistry =
            std::make_shared<facebook::react::ComponentDescriptorProviderRegistry>();
        for (auto componentDescriptorProvider : createComponentDescriptorProviders()) {
            componentDescriptorProviderRegistry->add(componentDescriptorProvider);
        }

        return componentDescriptorProviderRegistry;
    }
}