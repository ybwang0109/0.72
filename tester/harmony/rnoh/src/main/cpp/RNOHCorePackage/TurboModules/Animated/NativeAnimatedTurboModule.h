#pragma once

#include <mutex>
#include <react/renderer/core/ReactPrimitives.h>
#include <react/renderer/core/EventListener.h>
#include <RNOH/ArkTSTurboModule.h>
#include <folly/dynamic.h>
#include <native_vsync/native_vsync.h>

#include "AnimatedNodesManager.h"
#include "RNOH/NativeVsyncHandle.h"
#include "RNOH/EventEmitRequestHandler.h"

namespace rnoh {

class NativeAnimatedTurboModule : public rnoh::ArkTSTurboModule, public rnoh::EventEmitRequestHandler, public std::enable_shared_from_this<NativeAnimatedTurboModule> {

  public:
    using Context = rnoh::ArkTSTurboModule::Context;

    NativeAnimatedTurboModule(const ArkTSTurboModule::Context ctx, const std::string name);
    ~NativeAnimatedTurboModule() override;

    void startOperationBatch();

    void finishOperationBatch();

    void createAnimatedNode(facebook::react::Tag tag, folly::dynamic const &config);

    void updateAnimatedNodeConfig(facebook::react::Tag tag, facebook::jsi::Value const &config);

    double getValue(facebook::react::Tag tag);

    void startListeningToAnimatedNodeValue(facebook::jsi::Runtime &rt, facebook::react::Tag tag);

    void stopListeningToAnimatedNodeValue(facebook::react::Tag tag);

    void connectAnimatedNodes(facebook::react::Tag parentTag, facebook::react::Tag childTag);

    void disconnectAnimatedNodes(facebook::react::Tag parentTag, facebook::react::Tag childTag);

    void startAnimatingNode(
        facebook::react::Tag animationId,
        facebook::react::Tag nodeTag,
        folly::dynamic const &config,
        std::function<void(bool)> &&endCallback);

    void stopAnimation(facebook::react::Tag animationId);

    void setAnimatedNodeValue(facebook::react::Tag nodeTag, double value);

    void setAnimatedNodeOffset(facebook::react::Tag nodeTag, double offset);

    void flattenAnimatedNodeOffset(facebook::react::Tag nodeTag);

    void extractAnimatedNodeOffset(facebook::react::Tag nodeTag);

    void connectAnimatedNodeToView(facebook::react::Tag nodeTag, facebook::react::Tag viewTag);

    void disconnectAnimatedNodeFromView(facebook::react::Tag nodeTag, facebook::react::Tag viewTag);

    void restoreDefaultValues(facebook::react::Tag nodeTag);

    void dropAnimatedNode(facebook::react::Tag tag);

    void addAnimatedEventToView(facebook::react::Tag viewTag, std::string const &eventName, folly::dynamic const &eventMapping);

    void removeAnimatedEventFromView(facebook::react::Tag viewTag, std::string const &eventName, facebook::react::Tag animatedValueTag);

    void addListener(std::string const &eventName);

    void removeListeners(double count);

    void runUpdates();

    void setNativeProps(facebook::react::Tag tag, folly::dynamic const &props);

    void emitAnimationEndedEvent(facebook::jsi::Runtime &rt, facebook::react::Tag animationId, bool completed);

    // EventEmitRequestHandler
    void handleEvent(EventEmitRequestHandler::Context const &ctx) override;

  private:
    std::unique_lock<std::mutex> acquireLock() {
        return std::unique_lock(m_nodesManagerLock);
    }

    // `shared_from_this` cannot be used in constructor,
    // so we defer the initialization of the event listener
    // until the first animated event is registered.
    void initializeEventListener();

    NativeVsyncHandle m_vsyncHandle;
    AnimatedNodesManager m_animatedNodesManager;
    std::mutex m_nodesManagerLock;
    bool m_initializedEventListener = false;
};

} // namespace rnoh