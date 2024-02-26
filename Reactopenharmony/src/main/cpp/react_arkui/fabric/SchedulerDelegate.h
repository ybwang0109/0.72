#pragma once
#include <react/renderer/scheduler/SchedulerDelegate.h>
#include <folly/dynamic.h>

#include "react_arkui/ArkTSChannel.h"

#include "react_arkui/fabric/fabric_mounting_manager.h"

namespace rnoh {

class SchedulerDelegate : public facebook::react::SchedulerDelegate {
  public:
    SchedulerDelegate(fabric_mounting_manager* fabric_mounting_manager, ArkTSChannel::Shared arkTsChannel)
        : fabricMountingManager_(fabric_mounting_manager),
          m_arkTsChannel(arkTsChannel){};

    ~SchedulerDelegate() = default;

    void schedulerDidFinishTransaction(facebook::react::MountingCoordinator::Shared mountingCoordinator) override {
        fabricMountingManager_->executeMount(std::move(mountingCoordinator));
    }

    void schedulerDidRequestPreliminaryViewAllocation(facebook::react::SurfaceId surfaceId, const facebook::react::ShadowNode &shadowNode) override {
        
        if (!shadowNode.getTraits().check(ShadowNodeTraits::Trait::FormsView)) {
            return;
        }
        auto shadowView = facebook::react::ShadowView(shadowNode);
        fabricMountingManager_->preallocateShadowView(surfaceId, shadowView);
    }

    void schedulerDidDispatchCommand(const facebook::react::ShadowView &shadowView, std::string const &commandName, folly::dynamic const &args) override {   
    }

    void schedulerDidSendAccessibilityEvent(const facebook::react::ShadowView &shadowView, std::string const &eventType) override {
    }

    void schedulerDidSetIsJSResponder(
        facebook::react::ShadowView const &shadowView, bool isJSResponder, bool blockNativeResponder) override {
        folly::dynamic payload = folly::dynamic::object;
        payload["tag"]= shadowView.tag;
        payload["isJSResponder"] = isJSResponder;
        payload["blockNativeResponder"] = blockNativeResponder;
        m_arkTsChannel->postMessage("SCHEDULER_DID_SET_IS_JS_RESPONDER", payload);
    }

  private:
      fabric_mounting_manager *fabricMountingManager_;
      ArkTSChannel::Shared m_arkTsChannel;
};

} // namespace rnoh
