//
// Created on 2024/1/17.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
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


#include "RNOHFabricUIManager.h"
#include "react_arkui/native_instance/native_catalyst_instance.h"

#include "react_arkui/EventBeat.h"
#include "react_arkui/ShadowViewRegistry.h"
#include "react_arkui/NativeLogger.h"
#include <hilog/log.h>

#include "react_arkui/LogSink.h"

#define LOG_TAG "RTNArkUI_CPP"

const std::string instanceName = "testInstance";

using namespace facebook;
namespace rnoh {

std::unique_ptr<RNOHFabricUIManager> RNOHFabricUIManager::FabricInstances;
void addInstanceToStaticVariable(RNOHFabricUIManager *inputInstance) {
    std::unique_ptr<RNOHFabricUIManager> temp;  
    temp.reset(inputInstance);
    RNOHFabricUIManager::FabricInstances = std::move(temp);
}

RNOHFabricUIManager::RNOHFabricUIManager(fabric_mounting_manager *mountingManager)
    : fabricMountingManager_(mountingManager),
      m_contextContainer(std::make_shared<facebook::react::ContextContainer>()),
      m_arkTsChannel(nullptr),
      scheduler(nullptr),
      m_shouldRelayUITick(false),
      m_uiTicker(std::make_shared<UITicker>()) {

    LogSink::initializeLogging();
    OH_LOG_ERROR(LOG_APP, "RNOHFabricUIManager::RNOHFabricUIManager()");

    this->unsubscribeUITickListener = this->m_uiTicker->subscribe(1, [this]() {
        this->taskExecutor->runTask(TaskThread::MAIN, [this]() {
            this->onUITick();
        });
    });

    this->instance = native_catalyst_instance::instancesByName[instanceName]->instance_;
    this->taskExecutor = native_catalyst_instance::instancesByName[instanceName]->taskExecutor;

    addInstanceToStaticVariable(this); // todo:临时通过全局变量管理实例，需要该实例应该由JS实例持有
}

RNOHFabricUIManager::~RNOHFabricUIManager() {
    if (this->unsubscribeUITickListener != nullptr) {
        unsubscribeUITickListener();
    }

    for (auto surfaceHandle : this->surfaceHandlers) {
        surfaceHandle.second->stop();
        scheduler->unregisterSurface(*surfaceHandle.second);
    }
}

void RNOHFabricUIManager::registryMeasureTextFnRef(ArkMeasureTextFunc measureTextFnRef) {
    //todo：临时先人为保证在initializeScheduler前注册相关的方法，后面应该改为与FabricUIManager方法直接绑定。
    OH_LOG_ERROR(LOG_APP, "RNOHFabricUIManager::registrymeasureTextFnRef()");
    m_measureTextFnRef = measureTextFnRef;
}

void RNOHFabricUIManager::initializeScheduler(component_factory *componentFactory) {
    LOG(ERROR) << "RNOHFabricUIManager:: initializeScheduler component_factory this is " << componentFactory << "\n";
    OH_LOG_ERROR(LOG_APP, "RNOHFabricUIManager::initializeScheduler()");

    auto textMeasurer = std::make_shared<TextMeasurer>(aki::JSBind::GetScopedEnv(), m_measureTextFnRef, taskExecutor);
    m_contextContainer->insert("textLayoutManagerDelegate", textMeasurer);

    auto reactConfig = std::make_shared<react::EmptyReactNativeConfig>();
    m_contextContainer->insert("ReactNativeConfig", std::move(reactConfig)); 

    react::EventBeat::Factory eventBeatFactory = [taskExecutor = std::weak_ptr(taskExecutor), runtimeExecutor = this->instance->getRuntimeExecutor()](auto ownerBox) {
        return std::make_unique<EventBeat>(taskExecutor, runtimeExecutor, ownerBox);
    };

    auto backgroundExecutor = [executor = this->taskExecutor](std::function<void()> && callback) {
        executor->runTask(TaskThread::BACKGROUND, std::move(callback));
    };

    react::SchedulerToolbox schedulerToolbox{
        .contextContainer = m_contextContainer,
        .componentRegistryFactory = componentFactory->buildRegistryFunction,
        .runtimeExecutor = this->instance->getRuntimeExecutor(),
        .asynchronousEventBeatFactory = eventBeatFactory,
        .synchronousEventBeatFactory = eventBeatFactory,
        .backgroundExecutor = backgroundExecutor,
    };

    fabricMountingManager_->taskExecutor = taskExecutor;
    this->schedulerDelegate =
        std::make_unique<SchedulerDelegate>(fabricMountingManager_, m_arkTsChannel);
    m_animationDriver = std::make_shared<react::LayoutAnimationDriver>(
        this->instance->getRuntimeExecutor(), m_contextContainer, this);
    this->scheduler = std::make_unique<react::Scheduler>(schedulerToolbox, m_animationDriver.get(), schedulerDelegate.get());
}

void RNOHFabricUIManager::startSurfaceWithConstraints(react::Tag surfaceId,
                                                      std::string const &appKey,
                                                      napi_value initialProps,
                                                      float width,
                                                      float height,
                                                      float viewportOffsetX,
                                                      float viewportOffsetY,
                                                      float pixelRatio) {
    ArkJS arkJs(aki::JSBind: :GetScopedEnv());
    OH_LOG_ERROR(LOG_APP, "RNOHFabricUIManager::startSurfaceWithConstraints() ");

    if (surfaceHandlers.count(surfaceId)) {
        LOG(ERROR) << "createSurface: Surface with surface id " << surfaceId << " already exists.";
        return;
    }
    auto surfaceHandler = std::make_shared<react::SurfaceHandler>(appKey, surfaceId);

    this->scheduler->registerSurface (*surfaceHandler);
    surfaceHandlers.insert({surfaceId, std::move(surfaceHandler)});

    try {
        auto it = surfaceHandlers.find(surfaceId);
        if (it == surfaceHandlers.end()) {
            LOG(ERROR) << "startSurface: No surface with id " << surfaceId;
            return;
        }

        auto surfaceHandler = it->second;
        surfaceHandler->setProps(std::move(arkJs.getDynamic(initialProps)));
        auto layoutConstraints = surfaceHandler->getLayoutConstraints();
        layoutConstraints.layoutDirection = react::LayoutDirection::LeftToRight;
        layoutConstraints.minimumSize = layoutConstraints.maximumSize = {
            .width = width,
            .height = height};
        auto layoutContext = surfaceHandler->getLayoutContext();
        surfaceHandler->setDisplayMode(react::DisplayMode::Suspended);
        layoutContext.viewportOffset = {viewportOffsetX, viewportOffsetY};
        layoutContext.pointScaleFactor = pixelRatio;
        surfaceHandler->constraintLayout(layoutConstraints, layoutContext);
        LOG(INFO) << "startSurface::starting: surfaceId=" << surfaceId;
        surfaceHandler->start();
        LOG(INFO) << "startSurface::started surfaceId=" << surfaceId;
        auto mountingCoordinator = surfaceHandler->getMountingCoordinator();
        mountingCoordinator->setMountingOverrideDelegate(m_animationDriver);
    } catch (const std::exception &e) {
        LOG(ERROR) << "startSurface: " << e.what() << "\n";
        throw e;
    };

    this->setSurfaceDisplayMode(surfaceId, facebook::react::DisplayMode::Visible);
}

void RNOHFabricUIManager::setSurfaceProps(facebook::react::Tag surfaceId, folly::dynamic &&props) {
    auto it = surfaceHandlers.find(surfaceId);
    if (it == surfaceHandlers.end()) {
        LOG(ERROR) << "setSurfaceProps: No surface with id " << surfaceId;
        return;
    }
    it->second->setProps(std::move(props));
}

void RNOHFabricUIManager::stopSurface(react::Tag surfaceId) {
    auto it = surfaceHandlers.find(surfaceId);
    if (it == surfaceHandlers.end()) {
    LOG(ERROR) << "stopSurface: No surface with id " << surfaceId;
    return;
    }
    auto surfaceHandle = it->second;
    // stopping on main thread asynchronously caused dead lock
    LOG(INFO) << "stopSurface: stopping " << surfaceId;
    try {
        surfaceHandle->stop();
        LOG(INFO) << "stopSurface: stopped " << surfaceId;
    } catch (const std::exception &e) {
        LOG(ERROR) << "stopSurface: failed - " << e.what() << "\n";
        throw e;
    };
}

void RNOHFabricUIManager::destroySurface (react: :Tag surfaceId) {
    auto it = surfaceHandlers.find(surfaceId);
    if (it == surfaceHandlers.end()) {
        LOG(ERROR) << "destroySurface: No surface with id " << surfaceId;
        return;
    }
    scheduler->unregisterSurface (*it->second);
    surfaceHandlers.erase(it);
}

void RNOHFabricUIManager::setSurfaceDisplayMode(facebook::react::Tag surfaceId, facebook::react::DisplayMode displayMode) {
    try {
        auto surfaceIt = surfaceHandlers.find(surfaceId);
        if (surfaceIt == surfaceHandlers.end()) {
            LOG(ERROR) << "setSurfaceDisplayMode: No surface with id " << surfaceId;
            return;
        }
        auto surfaceHandler = surfaceIt->second;
        taskExecutor->runTask(TaskThread::JS, [this, surfaceHandler, displayMode]() {
            surfaceHandler->setDisplayMode(displayMode);
        });
    } catch (const std::exception &e) {
        LOG(ERROR) << "setSurfaceDisplayMode: " << e.what() << "\n";
        throw e;
    }
}

void RNOHFabricUIManager::updateSurfaceConstraints(react::Tag surfaceId, float width, float height, float viewportOffsetX, float viewportOffsetY, float pixelRatio) {
    try{
        if (surfaceHandlers.count(surfaceId)== 0) {
        LOG(ERROR) << "updateSurfaceConstraints: No surface with id " << surfaceId;
        return;
        }
        taskExecutor->runTask(TaskThread::MAIN, [this, surfaceId, width, height, viewportOffsetX, viewportOffsetY, pixelRatio]() {
            auto layoutConstraints = surfaceHandlers [surfaceId]->getLayoutConstraints();
            layoutConstraints.minimumSize = layoutConstraints.maximumSize = {
                .width = width,
                .height = height};
            auto layoutContext = surfaceHandlers[surfaceId]->getLayoutContext();
            layoutContext.viewportOffset = {viewportOffsetX, viewportOffsetY};
            layoutContext.pointScaleFactor = pixelRatio;
            surfaceHandlers[surfaceId]->constraintLayout(layoutConstraints, layoutContext);
        });
    } catch (const std::exception &e) {
        LOG(ERROR) << "updateSurfaceConstraints: " << e.what() << "\n";
        throw e;
    };
}

void RNOHFabricUIManager::emitComponentEvent(napi_env env, react::Tag tag, std::string eventName, napi_value payload) {

}

void RNOHFabricUIManager::onUITick() {
    if (this->m_shouldRelayUITick.load()) {
        this->scheduler->animationTick();
    }
}

void RNOHFabricUIManager::onAnimationStarted() {
    m_shouldRelayUITick.store (true);
}

void RNOHFabricUIManager::onAllAnimationsComplete() {
    m_shouldRelayUITick.store (false);
}

} //namespace rnoh
