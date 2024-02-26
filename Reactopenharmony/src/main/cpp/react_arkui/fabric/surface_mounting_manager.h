//
// Created on 2024/2/4.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h"

#ifndef SURFACE_MOUNTING_MANAGER_H
#define SURFACE_MOUNTING_MANAGER_H

#include <aki/jsbind.h>
#include <linux/dvb/frontend.h>
#include <unordered_map>
#include "react_arkui/fabric/arkui_view.h"
#include "react_arkui/fabric/view_state.h"

#include <react/renderer/mounting/ShadowView.h>


using namespace facebook::react;

namespace rnoh {

    class surface_mounting_manager {

    public:
        surface_mounting_manager(SurfaceId SurfaceId_);
        ~surface_mounting manager() {}

        void bindingArkTsParty(aki::Value arkTS);

        void registryViewManager(std::string managerName, view_manager<arkui_view> *viewManager);

        bool isStopped();

        void preallocateView(Tag tag, ComponentName componentName, folly::dynamic props, State::Shared state,
                             EventEmitter::Shared eventEmitter, bool isLayoutable);

        void createView(Tag tag, ComponentName componentName, folly::dynamic props, State::Shared state,
                        EventEmitter::Shared eventEmitter,bool isLayoutable);

        void deleteView(Tag tag);
        void addViewAt(Tag parentTag, Tag tag, int index);
        void removeViewAt(Tag tag, Tag parentTag, int index) {}
        void removeDeleteTreeAt(Tag tag, Tag parentTag, int index) {}
        void updateProps(int reactTag, folly::dynamic props) {}
        void updateLayout(int reactTag, int parentTag, int x, int y, int width, int height, int displayType){}
        void updateState(int reactTag,State::Shared state){}
        void updatePadding(int reactTag, int left, int top, int right, int bottom){}
        void updateOverflowInset(int reactTag, int overflowInsetLeft, int overflowInsetTop, int overflowInsetRight, 
                                 int overflowInsetBottom){}
        void updateEventEmitter(int reactTag, EventEmitter::Shared eventEmitter){}

    private:
        void createViewOnMainThread(Tag tag, ComponentName componentName, folly: :dynamic props, State::Shared state,
                                    EventEmitter::Shared, bool isLayoutable);
        std::shared_ptr<view_state> getNullableViewState(Tag tag);
        void onViewStateDeleted(std::shared_ptr<view_state> viewState);

        aki::Value arkTsThis_;
        SurfaceId SurfaceId_;
        std::unordered_map<Tag, std::shared_ptr<view_state>> TagToViewState_;
        std::unordered_map<std::string, view_manager<arkui_view> *> ViewManagerRegistry_;
        bool mIsStopped = false;
    };

    JSBIND_CLASS(surface_mounting_manager) {
        JSBIND_CONSTRUCTOR<SurfaceId>();
        JSBIND_METHOD(bindingArkTsParty);
        JSBIND_METHOD(registryViewManager);
    }
} // namespace rnoh
#endif // SURFACE_MOUNTING_MANAGER_H

