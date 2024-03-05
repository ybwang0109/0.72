//
// Created on 2024/2/25.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
 
#ifndef ROOTVIEW_H
#define ROOTVIEW_H
 
#include "react_arkui/LogSink.h"
#include "react_arkui/fabric/arkui_view.h"
 
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <arkui/native_interface.h>
#include <arkui/native_node.h>
 
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <arkui/native_interface.h>
#include <arkui/native_node.h>
 
namespace rnoh {
    class RootView : public arkui_view {
    public:
        RootView() {
            LOG(ERROR) << "RootView::RootView create. this is " << this << "\n";
            createNode();
        }
 
        void attachedToWindow(OH_NativeXComponent * XComponentWindow){
            int32_t ret =
                OH_NativeXComponent_AttachNativeRootNode(XComponentWindow, rootNode_);
            LOG(ERROR) << "surface_mounting_manager: end AttachNativeRootNode ret = " << ret;
        }
 
        ArkUI_NodeHandle rootNode_ = nullptr;
 
    private:
        void createNode();
    };
} // namespace rnoh
 
#endif //72_5_NEW_DEV_ROOTVIEW_H