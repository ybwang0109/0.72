//
// Created on 2024/2/4.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h"

#include "surface_mounting_manager.h"
#include "react_arkui/LogSink.h"
#include "react_arkui/fabric/arkui_view.h"
#include "react_arkui/fabric/view_state.h"

namespace rnoh {

    bool surface_mounting_manager::isStopped() { return mIsStopped; }

    surface_mounting_manager::surface_mounting_manager(SurfaceId SurfaceId): SurfaceId_(SurfaceId) {
        LOG(ERROR) << "surface_mounting_manager::surface_mounting_manager. SurfaceId is  " << SurfaceId_ << "\n";
    }

    void surface_mounting_manager::bindingArkTsParty(aki::Value arkTS) {
        LOG(ERROR) << "surface_mounting_manager::bindingArkTsParty. this is  " << this << "\n";
        arkTsThis_ = arkTS;
    }

    void surface_mounting_manager::registryViewManager(std::string managerName, view_manager<arkui_view> *viewManager) {
        LOG(ERROR) << "surface_mounting_manager::registryViewManager view_manager. name is  " << managerName << "\n";
        ViewManagerRegistry_.insert_or_assign(managerName, viewManager);
    }

    void surface_mounting_manager::preallocateView(Tag tag, ComponentName componentName, folly::dynamic props,
                                                   State::Shared state, EventEmitter::Shared eventEmitter,
                                                   bool isLayoutable) {
        LOG(ERROR) << "surface_mounting_manager::preallocateView. this is  " << this << "\n";
        LOG(ERROR) << "surface_mounting_manager::preallocateView. reactTag is  " << tag << "\n";

        if (isStopped()) {
            return;
        }
        if (getNullableViewState(tag) != nullptr) {
            return;
        }

        createViewOnMainThread(tag, componentName, props, state,eventEmitter,isLayoutable);
    }

    void surface_mounting_manager::createView(Tag tag, ComponentName componentName, folly::dynamic props,
                                                State::Shared state, EventEmitter::Shared eventEmitter, bool isLayoutable) { 
        LOG(ERROR) << "surface_mounting_manager::createView. this is  " << this << "\n";
        LOG(ERROR) << "surface_mounting_manager::createView. reactTag is  " << tag <<"\n";
        if (isStopped()) {
            return;
        }
        std::shared_ptr<view_state> viewState = getNullableViewState(tag);
        if (viewState != nullptr && viewState->View_ !=nullptr) {
            return;
        }
        createViewOnMainThread(tag, componentName, props, state, eventEmitter, isLayoutable);
    }

    void surface_mounting_manager::createViewOnMainThread(Tag reactTag, ComponentName componentName,
                                                            folly::dynamic props,State::Shared state,
                                                            EventEmitter::Shared eventEmitter,bool isLayoutable) {
        LOG(ERROR) << "surface_mounting_manager::createViewOnMainThread. reactTag is  " << reactTag << "\n";
        view_manager<arkui_view> *viewManager = nullptr;
        arkui_view *view = nullptr;

        if (isLayoutable) {
            LOG(ERROR) << "surface_mounting_manager::createViewOnMainThread get view_manager name is " <<componentName;
            auto it = ViewManagerRegistry_.find(componentName);
            if (it == ViewManagerRegistry_.end()) { 
                LOG(ERROR) << "surface_mounting_manager::createViewOnMainThread get view_manager error!";
                return;
            }

            viewManager = it->second;
            view = viewManager->createView(reactTag, props, state, eventEmitter);
        }

        auto viewState = std::make_shared<view_state>(reactTag, view, viewManager);

        viewState->props = props;
        viewState->state = state;
        viewState->eventEmitter = eventEmitter;

        TagToViewState_.insert_or_assign(reactTag, viewState);
    }

    void surface_mounting_manager::deleteView(Tag reactTag) {
        if (isStopped()) {
            return;
        }
        std::shared_ptr<view_state> viewState = getNullableViewState(reactTag);
        if (viewState == nullptr) {
//              ReactSoftExceptionLogger.logSoftException(
//                   MountingManager.TAG,
//                   new IllegalStateException("Unable to find viewState for tag: " + reactTag + " for deleteView"));
            return;
        }
        // To delete we simply remove the tag from the registry.
        // We want to rely on the correct set of MountInstructions being sent to the platform,
        //or StopSurface being called, so we do not handle deleting descendents of the View
        TagToViewState_.erase(reactTag);
        onViewStateDeleted(std::move(viewState));
    }

    void surface_mounting_manager::addViewAt(Tag parentTag, Tag tag, int index) {}

    
    std::shared_ptr<view_state> surface_mounting_manager::getNullableViewState(Tag tag) {
        auto it = TagToViewState_.find(tag);
        if (it == TagToViewState_.end()) {
            return nullptr;
        }
        return it->second;
    }

    void surface_mounting_manager::onViewStateDeleted(std::shared_ptr<view_state> viewState) {
        view_manager<arkui_view> *viewManager = viewState->ViewManager_;
        if (!viewState->mIsRoot && viewManager != nullptr) {
            //  viewManager->onDropViewInstance(viewState->View);
        }
    
    }
    } // namespace rnoh
