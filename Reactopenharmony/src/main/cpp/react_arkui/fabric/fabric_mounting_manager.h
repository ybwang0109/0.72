//
//Created on 2024/2/4.
//
// Node APIs are not fully supported, To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h"

#ifndef FABRIC_MOUNTING_MANAGER_H
#define FABRIC_MOUNTING_MANAGER_H

#include "react_arkui/TaskExecutor/TaskExecutor.h"
#include <react/renderer/mounting/MountingCoordinator.h>
#include "react_arkui/shadowViewRegistry.h"
#include <set.h>

#include "react_arkui/fabric/surface_mounting_manager.h"

#include <aki/jsbind.h>

using namespace facebook;
using namespace facebook::react;

namespace rnoh{

    class fabric_mounting_manager {

    public:
        fabric_mounting_manager();
        ~fabric_mounting_manager() {}

        void bindingArkTsParty(aki::Value arkTS);
        void preallocateShadowView(SurfaceId surfaceld, ShadowView const &shadowView);
        void executeMount(MountingCoordinator::Shared mountingCoordinator);
        void onSurfaceStart(Surfaceld surfaceld, surface_mounting_manager* surface_manager);
        surface_mounting_manager* getSurfaceManager(Surfaceld surfaceId) ;

        std::shared_ptr<TaskExecutor> taskExecutor;

    private:
        aki::Value arkTsThis_;
        butter::map<Surfaceld, butter::set<Tag>> allocatedViewRegistry_{};
        std::unordered_map<facebook::react::Surfaceld, surface_mounting_manager*> surfaceMountingManagerByID_;
        std::recursive_mutexallocatedViewsMutex_;
    };
    
    JSBIND_CLASS(fabric_mounting_manager) {
        JSBIND_CONSTRUCTOR<>();
        JSBIND_METHD(bindingArkTsParty);
        JSBIND_METHD(onSurfaceStart);
    }
} // namespace rnoh
#endif // FABRIC_MOUNTING_MANAGER_H


