//
// Created on 2024/2/25.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".
 
#include "RootView.h"
 
namespace rnoh {
    void RootView::createNode() {
        LOG(ERROR) << "RootView::createNode. this is " << this << "\n";
        auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1));
 
        if (nodeAPI == nullptr) {
            LOG(ERROR) << "RootView: nodeAPI null !!!!!! \n";
            return;
        }
 
        rootNode_ = nodeAPI->createNode(ARKUI_NODE_STACK);
 
        ArkUI_NumberValue widthValue[] = {388};
        ArkUI_AttributeItem widthItem = {widthValue, 1};
        nodeAPI->setAttribute(rootNode_, NODE_WIDTH, &widthItem);
 
        ArkUI_NumberValue heightValue1[] = {500};
        ArkUI_AttributeItem heightItem1 = {heightValue1, 1};
        nodeAPI->setAttribute(rootNode_, NODE_HEIGHT, &heightItem1);
 
        ArkUI_NumberValue value[] = {0, 0};
        ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue)};
        nodeAPI->setAttribute(rootNode_, NODE_POSITION, &item);
 
        ArkUI_NumberValue colorValue[] = {{.u32 = 0xFFFF8000}};
        ArkUI_AttributeItem colorItem = {colorValue, 1};
        nodeAPI->setAttribute(rootNode_, NODE_BACKGROUND_COLOR, &colorItem);
    }
}