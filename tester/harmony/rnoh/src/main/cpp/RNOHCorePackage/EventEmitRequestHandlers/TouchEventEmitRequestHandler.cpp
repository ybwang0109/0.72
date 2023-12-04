#include <glog/logging.h>
#include <react/renderer/components/view/TouchEventEmitter.h>
#include "TouchEventEmitRequestHandler.h"

using namespace facebook;

namespace rnoh {

void TouchEventEmitRequestHandler::handleEvent(TouchEventEmitRequestHandler::Context const &ctx) {
    if (ctx.eventName != "Touch") {
        return;
    }

    ArkJS arkJs(ctx.env);
    auto touchEvent = ctx.payload;

    auto timestampNanos = arkJs.getDouble(arkJs.getObjectProperty(touchEvent, "timestamp"));
    react::Float timestamp = timestampNanos / 1e6;

    auto touches = convertTouches(arkJs, ctx.tag, timestamp, arkJs.getObjectProperty(touchEvent, "touches"));
    auto changedTouches = convertTouches(arkJs, ctx.tag, timestamp, arkJs.getObjectProperty(touchEvent, "changedTouches"));

    auto eventType = (TouchType)(arkJs.getDouble(arkJs.getObjectProperty(ctx.payload, "type")));
    bool isTouchEnd = eventType == TouchType::UP || eventType == TouchType::CANCEL;

    std::unordered_set<react::Tag> changedTargets;
    for (auto &touch : changedTouches) {
        changedTargets.insert(touch.target);
    }

    for (auto target : changedTargets) {
        auto eventEmitter = ctx.shadowViewRegistry->getEventEmitter<react::TouchEventEmitter>(target);
        if (!eventEmitter) {
            continue;
        }

        react::TouchEvent event {
            .touches = touches,
            .changedTouches = changedTouches
        };

        react::Touches targetTouches;
        for (auto &touch : touches) {
            if (touch.target == target) {
                targetTouches.insert(touch);
            }
        }
        
        event.targetTouches = std::move(targetTouches);

        switch (eventType) {
        case TouchType::DOWN:
            eventEmitter->onTouchStart(event);
            break;
        case TouchType::UP:
            eventEmitter->onTouchEnd(event);
            break;
        case TouchType::MOVE:
            eventEmitter->onTouchMove(event);
            break;
        case TouchType::CANCEL:
            eventEmitter->onTouchCancel(event);
            break;
        default:
            LOG(FATAL) << "Invalid touch event type received from Ark";
        }
    }
}

facebook::react::Touch TouchEventEmitRequestHandler::convertTouchObject(ArkJS &arkJs, napi_value touchObject) {
    facebook::react::Tag id = arkJs.getDouble(arkJs.getObjectProperty(touchObject, "id"));
    facebook::react::Tag target = arkJs.getDouble(arkJs.getObjectProperty(touchObject, "targetTag"));
    facebook::react::Float screenX = arkJs.getDouble(arkJs.getObjectProperty(touchObject, "screenX"));
    facebook::react::Float screenY = arkJs.getDouble(arkJs.getObjectProperty(touchObject, "screenY"));
    facebook::react::Float pageX = arkJs.getDouble(arkJs.getObjectProperty(touchObject, "pageX"));
    facebook::react::Float pageY = arkJs.getDouble(arkJs.getObjectProperty(touchObject, "pageY"));
    facebook::react::Float x = arkJs.getDouble(arkJs.getObjectProperty(touchObject, "x"));
    facebook::react::Float y = arkJs.getDouble(arkJs.getObjectProperty(touchObject, "y"));
    return facebook::react::Touch{
        .pagePoint = {.x = pageX, .y = pageY},
        .offsetPoint = {.x = x, .y = y},
        .screenPoint = {.x = screenX, .y = screenY},
        .identifier = id,
        .target = target,
        .force = 1};
}

facebook::react::Touches TouchEventEmitRequestHandler::convertTouches(ArkJS &arkJs, facebook::react::Tag tag, facebook::react::Float timestamp, napi_value touchArray) {
    facebook::react::Touches touches;
    auto arrayLength = arkJs.getArrayLength(touchArray);
    for (int i = 0; i < arrayLength; i++) {
        auto touchObject = arkJs.getArrayElement(touchArray, i);
        auto touch = convertTouchObject(arkJs, touchObject);
        touch.timestamp = timestamp;

        touches.insert(std::move(touch));
    }
    return touches;
}

}