//
// Created on 2024/1/17.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// Please include "napi/native_api.h".

#ifndef HARMONY_RNOHFABRICUIMANAGER_H
#define HARMONY_RNOHFABRICUIMANAGER_H
#include <napi/native_api.h>
#include <functional>

#include <cxxreact/Instance.h>
#include <react/renderer/scheduler/Scheduler.h>
#include <react/renderer/animations/LayoutAnimationDriver.h>
#include <react/renderer/componentregistry/ComponentDescriptorProviderRegistry.h>

#include "react_arkui/fabric/SchedulerDelegate.h"
#include "react_arkui/ShadowViewRegistry.h"
#include "react arkui/EventDispatcher.h"
#include "react_arkui/EventEmitRequestHandler.h"
#include "react_arkui/TaskExecutor/TaskExecutor.h"
#include "react_arkui/UITicker.h"
#include "react_arkui/ArkTSChannel.h"
#include "react_arkui/TextMeasurer.h"

#include "react_arkui/fabric/component_factory.h"
#include "react _arkui/fabric/fabric_mounting_manager.h"

#include <aki/jsbind.h>

namespace rnoh {

    class RNOHFabricUIManager : public facebook::react::LayoutAnimationStatusDelegate {

    public:
        RNOHFabricUIManager(fabric_mounting _manager* mountingManager);
        ~RNOHFabricUIManager ();

        void initializeScheduler(component_factory *componentFactory);
        void registryMeasureTextFnRef(std::function<napi_value(napi_value, napi_value, napi_value)> measureTextEnRef);
        void startSurfaceWithConstraints(facebook::react::Surfaceld surfaceld, std::string const &moduleName,
                                        napi _value initialProps, float width, float height, float viewportoffsetx,
                                        float viewportOffsetY, float pixelRatio); 
        void setSurfaceProps(facebook::react::Surfaceld surfaceld, folly::dynamic &&props);
        void stopSurface(facebook::react::Surfaceld surfaceId);
        void destroySurface(facebook::react::Surfaceld surfaceld);
        void updateSurfaceConstraints(facebook::react::Surfaceld surfaceld, float width, float height, float viewportoffsetX
                                        float viewportOffsetY, float pixelRatio);
        void setSurfaceDisplayMode(facebook::react::Surfaceld surfaceld, facebook::react::DisplayMode displayMode);
        void updatestate(napi_env env, std::string const &componentName, facebook::react::Tag tag, napi_value newState);
        void emitComponentEvent(napi_env env, facebook::react::Tag tag, std::string eventName, napi_value payload);

        void registryeventDispatcher(napi_env env, napi_ref napiEventDispatcherRef) {
        m_arkTsChannel - std::make shared<ArkTSChannel>(taskExecutor, ArkUS (env),napiEventDispatcherRef);
        }

        static std::unique ptr<RNOHFabricUIManager> FabricInstances

    private:
        napi_env_env;
        std::shared_ptr<facebook::react::Instance> instance;
        std::shared_ptr<TaskExecutor> taskExecutor;
        fabric_mounting manager* fabricMountingManager_;

        ArkTSChannel::Shared m_arkTsChannel;
        std::map<facebook::react::Tag, std::shared_ptr<facebook::react::SurfaceHandler>> surfaceHandlers;
        std::unique_ptr<facebook::react::Scheduler> scheduler;
        std::unique_ptr<SchedulerDelegate> schedulerDelegate;
        facebook::react::ContextContainer::Shared m_contextcontainer;
        std::shared_ptr<facebook::react::LayoutAnimationDriver> m_animationDriver;

        ArkMeasureTextFunc m_measureTextFnRef;

        UITicker::Shared m_uiTicker;
        std::atomic<bool> m_shouldRelayUITick;
        std::function<void()> unsubscribeUITickListener = nullptr;

        void onUITick();

        virtual void onAnimationStarted() override;       // react::LayoutAnimationStatusDelegate
        virtual void onAllAnimationsComplete() override;  // react::LayoutAnimationStatusDelegate
    };

    JSBIND_CLASS(RNOHFabricUIManager) {
        JSBIND_CONSTRUCTOR<fabric_mounting manager*>();
        JSBIND_METHOD(initializeScheduler);
        JSBIND_METHOD(registryMeasureTextFnRef);
        JSBIND_METHOD(startSurfaceWithConstraints);
    }
    
}// namespace rnoh
#endif // HARMONY_RNOHFABRICUIMANAGER_H




