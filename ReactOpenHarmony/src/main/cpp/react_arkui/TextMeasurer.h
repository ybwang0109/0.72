#pragma once
#include <react/renderer/graphics/Size.h>
#include <react/renderer/textlayoutmanager/TextLayoutManager.h>
#include <string>
#include "napi/native_api.h"
#include "react_arkui/TaskExecutor/TaskExecutor.h"

namespace rnoh {

using ArkMeasureTextFunc = std::function< napi_value(napi_value, napi_value, napi_value)>;

class TextMeasurer : public facebook::react::TextLayoutManagerDelegate {

  public:
    TextMeasurer(napi_env env, ArkMeasureTextFunc measureTextFnRef, std::shared_ptr<TaskExecutor> taskExecutor)
        : m_env(env),
          m_measureTextFnRef(measureTextFnRef),
          m_taskExecutor(taskExecutor) {}

    facebook::react::TextMeasurement measure(facebook::react::AttributedString attributedString,
                                   facebook::react::ParagraphAttributes paragraphAttributes,
                                   facebook::react::LayoutConstraints layoutConstraints);

  private:
    napi_env m_env;
    ArkMeasureTextFunc m_measureTextFnRef;
    std::shared_ptr<TaskExecutor> m_taskExecutor;
};
} // namespace rnoh
